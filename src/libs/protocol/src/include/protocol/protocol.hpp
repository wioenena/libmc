#ifndef LIBMC_PROTOCOL_PROTOCOL_HPP
#define LIBMC_PROTOCOL_PROTOCOL_HPP

#if defined(_WIN32) || defined(_WIN64)
#pragma once
#endif

#include <cstdint>

namespace libmc::protocol {
enum class ConnectionState : std::uint8_t {
  HANDSHAKING,
  STATUS,
  LOGIN,
  CONFIGURATION,
  PLAY,
};
} // namespace libmc::protocol

#endif // LIBMC_PROTOCOL_PROTOCOL_HPP