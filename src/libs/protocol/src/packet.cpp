#include "protocol/packet.hpp"

namespace libmc::protocol {

Packet::Packet(PacketId id) : mId(id) {}

[[nodiscard]] PacketId Packet::getId() const noexcept { return mId; }

[[nodiscard]] const std::vector<std::uint8_t> &
EncodablePacket::getData() const noexcept {
  return mData;
}
} // namespace libmc::protocol