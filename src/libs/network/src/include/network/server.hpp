#ifndef LIBMC_NETWORK_SERVER_HPP
#define LIBMC_NETWORK_SERVER_HPP

#include <boost/system/detail/error_code.hpp>
#include <cstdint>
#if defined(_WIN32) || defined(_WIN64)
#pragma once
#endif

#include <boost/asio.hpp>

namespace libmc::network {
using boost::asio::ip::tcp;

class Server {
public:
  Server(boost::asio::io_context &ioContext, std::uint16_t port);
  ~Server();

  void start();

private:
  tcp::acceptor mAcceptor;
  std::uint16_t mPort;

  void doAccept();
  void onAccept(tcp::socket socket);
};
} // namespace libmc::network

#endif // LIBMC_NETWORK_SERVER_HPP