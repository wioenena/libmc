#include "protocol/data_types.hpp"

namespace libmc::protocol {

[[nodiscard]] std::expected<std::int32_t, std::string>
decodeVarInt(std::span<const std::uint8_t> data, std::size_t &bytesRead) {
  std::int32_t value = 0;
  std::int32_t position = 0;
  std::uint8_t currentByte = 0;
  std::size_t dataSize = data.size();

  while (true) {
    if (bytesRead >= dataSize)
      return std::unexpected<std::string>(error_messages::OUT_OF_BOUNDS);

    currentByte = data[bytesRead++];
    value |= (currentByte & SEGMENT_BITS) << position;

    if ((currentByte & CONTINUE_BIT) == 0)
      break;

    position += VARINT_VARLONG__SIZE;

    if (position >= static_cast<std::int32_t>(MAX_VARINT_POSITION))
      return std::unexpected<std::string>(error_messages::VarIntTooBig);
  }

  return value;
}

[[nodiscard]] std::expected<std::int64_t, std::string>
decodeVarLong(std::span<const std::uint8_t> data, std::size_t &bytesRead) {
  std::int64_t value = 0;
  std::int32_t position = 0;
  std::uint8_t currentByte = 0;
  std::size_t dataSize = data.size();

  while (true) {
    if (bytesRead >= dataSize)
      return std::unexpected<std::string>(error_messages::OUT_OF_BOUNDS);

    currentByte = data[bytesRead++];
    value |= static_cast<std::int64_t>(currentByte & SEGMENT_BITS) << position;

    if ((currentByte & CONTINUE_BIT) == 0)
      break;

    position += VARINT_VARLONG__SIZE;

    if (position >= static_cast<std::int32_t>(MAX_VARLONG_POSITION))
      return std::unexpected<std::string>(error_messages::VarLongTooBig);
  }

  return value;
}
} // namespace libmc::protocol