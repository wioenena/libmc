#ifndef LIBMC_PROTOCOL_DATATYPES_HPP
#define LIBMC_PROTOCOL_DATATYPES_HPP

#if defined(_WIN32) || defined(_WIN64)
#pragma once
#endif

#include <cstddef>
#include <cstdint>
#include <expected>
#include <span>
#include <string>
#include <string_view>

namespace libmc::protocol {
constexpr std::uint8_t SEGMENT_BITS = 0x7F;
constexpr std::uint8_t CONTINUE_BIT = 0x80;
constexpr std::size_t VARINT_VARLONG_POSITION_INCREMENT_SIZE = 7;
constexpr std::size_t MAX_VARINT_POSITION = 32;
constexpr std::size_t MAX_VARLONG_POSITION = 64;

namespace error_messages {
inline constexpr std::string_view OUT_OF_BOUNDS = "Out of bounds";
inline constexpr std::string_view VarIntTooBig = "VarInt is too big";
inline constexpr std::string_view VarLongTooBig = "VarLong is too big";
} // namespace error_messages

[[nodiscard]] std::expected<std::int32_t, std::string>
decodeVarInt(std::span<const std::uint8_t> data, std::size_t &bytesRead);

[[nodiscard]] std::expected<std::int64_t, std::string>
decodeVarLong(std::span<const std::uint8_t> data, std::size_t &bytesRead);

} // namespace libmc::protocol

#endif // LIBMC_PROTOCOL_DATATYPES_HPP