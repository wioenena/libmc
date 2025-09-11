#ifndef LIBMC_NETWORK_SESSION_HPP
#define LIBMC_NETWORK_SESSION_HPP

#if defined(_WIN32) || defined(_WIN64)
#pragma once
#endif

#include "protocol/protocol.hpp"
#include <boost/asio.hpp>
#include <cstddef>
#include <memory>
#include <vector>

namespace libmc::network {
using boost::asio::ip::tcp;
class Session : public std::enable_shared_from_this<Session> {
public:
  Session(tcp::socket socket);
  ~Session();

  void start();

private:
  constexpr static std::size_t BUFFER_SIZE =
      1; // Minimum size for packet length. Packet length is a VarInt.
  constexpr static std::size_t MAX_PACKET_SIZE = (1 << 21) - 1;
  tcp::socket mSocket;
  std::vector<std::uint8_t> mBuffer;
  std::size_t mOffset = 0;
  [[maybe_unused]] protocol::ConnectionState mConnectionState =
      protocol::ConnectionState::HANDSHAKING;

  void doRead();
  void doReadPacketData(std::size_t packetSize);
  void onRead();
  void resetBuffer();
};
} // namespace libmc::network

#endif // LIBMC_NETWORK_SESSION_HPP