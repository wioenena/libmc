#include "protocol/data_types.hpp"
#include <stdexcept>

namespace libmc::protocol {

[[nodiscard]] std::int32_t decodeVarInt(std::span<const std::uint8_t> data,
                                        std::size_t &bytesRead) {
  std::int32_t value = 0;
  std::int32_t position = 0;
  std::uint8_t currentByte = 0;
  std::size_t dataSize = data.size();

  while (true) {
    if (bytesRead >= dataSize)
      throw std::runtime_error(std::string(error_messages::OUT_OF_BOUNDS));

    currentByte = data[bytesRead++];
    value |= (currentByte & SEGMENT_BITS) << position;

    if ((currentByte & CONTINUE_BIT) == 0)
      break;

    position += 7; // NOLINT(cppcoreguidelines-avoid-magic-numbers)

    if (position >= static_cast<std::int32_t>(MAX_VARINT_POSITION))
      throw std::runtime_error(std::string(error_messages::VarIntTooBig));
  }

  return value;
}

void encodeVarInt(std::int32_t value, std::vector<std::uint8_t> out) noexcept {
  while (true) {
    if ((value & ~SEGMENT_BITS) == 0) {
      out.push_back(static_cast<std::uint8_t>(value));
      break;
    }

    out.push_back(static_cast<std::uint8_t>(value & SEGMENT_BITS) |
                  CONTINUE_BIT);

    value = static_cast<std::int32_t>(
        static_cast<std::uint32_t>(value) >>
        7); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
  }
}

[[nodiscard]] std::int64_t decodeVarLong(std::span<const std::uint8_t> data,
                                         std::size_t &bytesRead) {
  std::int64_t value = 0;
  std::int32_t position = 0;
  std::uint8_t currentByte = 0;
  std::size_t dataSize = data.size();

  while (true) {
    if (bytesRead >= dataSize)
      throw std::runtime_error(std::string(error_messages::OUT_OF_BOUNDS));

    currentByte = data[bytesRead++];
    value |= static_cast<std::int64_t>(currentByte & SEGMENT_BITS) << position;

    if ((currentByte & CONTINUE_BIT) == 0)
      break;

    position += 7; // NOLINT(cppcoreguidelines-avoid-magic-numbers)

    if (position >= static_cast<std::int32_t>(MAX_VARLONG_POSITION))
      throw std::runtime_error(std::string(error_messages::VarLongTooBig));
  }

  return value;
}

void encodeVarLong(std::int64_t value, std::vector<std::uint8_t> out) noexcept {
  while (true) {
    if ((value & static_cast<std::int64_t>(~SEGMENT_BITS)) == 0) {
      out.push_back(static_cast<std::uint8_t>(value));
      break;
    }

    out.push_back(static_cast<std::uint8_t>(value & SEGMENT_BITS) |
                  CONTINUE_BIT);

    value = static_cast<std::int64_t>(
        static_cast<std::uint64_t>(value) >>
        7); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
  }
}

[[nodiscard]] std::string decodeString(std::span<const std::uint8_t> data,
                                       std::size_t &bytesRead) {
  std::int32_t length = decodeVarInt(data, bytesRead);

  if (bytesRead + length > data.size())
    throw std::runtime_error(std::string(error_messages::OUT_OF_BOUNDS));

  std::string value(data.begin() + static_cast<std::ptrdiff_t>(bytesRead),
                    data.begin() +
                        static_cast<std::ptrdiff_t>(bytesRead + length));
  bytesRead += length;
  return value;
}

void encodeString(const std::string &value,
                  std::vector<std::uint8_t> out) noexcept {
  std::size_t length = value.size();

  encodeVarInt(static_cast<std::int32_t>(length), out);
  out.insert(out.end(), value.begin(), value.end());
}

} // namespace libmc::protocol