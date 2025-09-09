#ifndef LIBMC_PROTOCOL_PACKET_HPP
#define LIBMC_PROTOCOL_PACKET_HPP

#if defined(_WIN32) || defined(_WIN64)
#pragma once
#endif

#include <cstdint>
#include <span>
#include <vector>

namespace libmc::protocol {

enum class PacketId : std::int32_t {};

class Packet {
public:
  explicit Packet(PacketId id);
#pragma message("TODO: Implement Packet::~Packet")
  virtual ~Packet() = default;
  [[nodiscard]] PacketId getId() const noexcept;

private:
  PacketId mId;
};

class EncodablePacket : public Packet {
public:
#pragma message("TODO: Implement EncodablePacket::~EncodablePacket")
  virtual ~EncodablePacket() = default;
#pragma message("TODO: Implement EncodablePacket::encode")
  [[nodiscard]] virtual const std::vector<std::uint8_t> &encode() const = 0;
#pragma message("TODO: Implement EncodablePacket::getData")
  [[nodiscard]] const std::vector<std::uint8_t> &getData() const noexcept;

protected:
  std::vector<std::uint8_t> mData;
};

class DecodablePacket : public Packet {
public:
#pragma message("TODO: Implement DecodablePacket::~DecodablePacket")
  virtual ~DecodablePacket() = default;
#pragma message("TODO: Implement DecodablePacket::decode")
  virtual void decode(const std::span<const std::uint8_t> &data,
                      std::size_t &offset) = 0;

private:
};

} // namespace libmc::protocol
#endif // LIBMC_PROTOCOL_PACKET_HPP