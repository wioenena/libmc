#include "protocol/datatypes.hpp"

namespace libmc::protocol {

[[nodiscard]] std::expected<std::int32_t, std::string>
decodeVarInt(const std::uint8_t *data, std::size_t &bytesRead) {
  std::int32_t value = 0;
  std::int32_t position = 0;
  std::uint8_t currentByte = 0;

  while (true) {
    currentByte = data[bytesRead++];
    value |= (currentByte & SEGMENT_BITS) << position;

    if ((currentByte & CONTINUE_BIT) == 0)
      break;

    position += VARINT_VARLONG__SIZE;

    if (position >= static_cast<std::int32_t>(MAX_VARINT_POSITION))
      return std::unexpected<std::string>("VarInt is too big");
  }

  return value;
}

[[nodiscard]] std::expected<std::int64_t, std::string>
decodeVarLong(const std::uint8_t *data, std::size_t &bytesRead) {
  std::int64_t value = 0;
  std::int32_t position = 0;
  std::uint8_t currentByte = 0;

  while (true) {
    currentByte = data[bytesRead++];
    value |= (currentByte & SEGMENT_BITS) << position;

    if ((currentByte & CONTINUE_BIT) == 0)
      break;

    position += VARINT_VARLONG__SIZE;

    if (position >= static_cast<std::int32_t>(MAX_VARLONG_POSITION))
      return std::unexpected<std::string>("VarLong is too big");
  }

  return value;
}
} // namespace libmc::protocol