#include "network/session.hpp"
#include <algorithm>
#include <boost/asio/buffer.hpp>
#include <boost/asio/read.hpp>
#include <boost/system/detail/error_code.hpp>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>
#include <protocol/data_types.hpp>
#include <span>
#include <string>
#include <vector>

namespace libmc::network {

Session::Session(tcp::socket socket)
    : mSocket(std::move(socket)), mBuffer(BUFFER_SIZE) {}

#pragma message("Implement Session::~Session")
Session::~Session() {
  if (mSocket.is_open()) {
    boost::system::error_code ec;
    mSocket.close(ec);
    if (ec) {
      std::cerr << "Error closing socket: " << ec.message() << "\n";
    } else {
      std::cout << "Socket closed successfully.\n";
    }
  }
}

void Session::start() { doRead(); }

void Session::doRead() {
  auto self(shared_from_this());

  mSocket.async_read_some(
      boost::asio::buffer(mBuffer, 1),
      [this, self](const boost::system::error_code &ec, std::size_t) {
        if (!ec) {
          auto bufferSpan = std::span<const std::uint8_t>(mBuffer);
          std::int32_t packetLength = 0;
          // Read the packet length VarInt recursively.
          try {
            packetLength = protocol::decodeVarInt(bufferSpan, mOffset);
          } catch (const std::runtime_error &e) {
            if (std::string(e.what()) ==
                std::string(protocol::error_messages::OUT_OF_BOUNDS)) {
              std::cout << "Waiting for packet length byte(s)...\n";
              doRead();
              return;
            }
          }

          if (packetLength > static_cast<std::int32_t>(MAX_PACKET_SIZE)) {
            std::cerr << "Packet length " << packetLength
                      << " exceeds maximum of " << MAX_PACKET_SIZE << "\n";
            return;
          }

          if (packetLength > 0) {
            mBuffer.erase(mBuffer.begin(),
                          mBuffer.begin() +
                              static_cast<std::ptrdiff_t>(mOffset));
            doReadPacketData(packetLength);
          }
        }
      });
}

void Session::doReadPacketData(std::size_t packetSize) {
  auto self(shared_from_this());

  std::size_t bufferSize = mBuffer.size();
  if (bufferSize < packetSize) {
    mBuffer.resize(packetSize);
  }

  boost::asio::async_read(
      mSocket, boost::asio::buffer(mBuffer, packetSize),
      [this, self](const boost::system::error_code &ec, std::size_t length) {
        if (!ec) {
          std::cout << "Read packet data of length " << length << "\n";
          // Set offset to 0 for decoding.
          mOffset = 0;
          onRead();
          // Reset buffer for next packet.
          resetBuffer();
          doRead(); // Read the next packet.
        }
      });
}

void Session::onRead() {
  std::span<const std::uint8_t> bufferSpan(mBuffer);
  std::int32_t packetId = protocol::decodeVarInt(bufferSpan, mOffset);
  std::cout << "Received packet with ID: " << packetId << "\n";
  // Reset mOffset for next packet.
  mOffset = 0;
}

void Session::resetBuffer() {
  mBuffer.resize(BUFFER_SIZE);
  std::ranges::fill(mBuffer, 0x00);
}

} // namespace libmc::network