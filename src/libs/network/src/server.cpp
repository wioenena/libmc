#include "network/server.hpp"
#include "network/session.hpp"
#include <iostream>
#include <memory>

namespace libmc::network {
Server::Server(boost::asio::io_context &ioContext, std::uint16_t port)
    : mAcceptor(ioContext, tcp::endpoint(tcp::v4(), port)), mPort(port) {}

#pragma message("Implement Server::~Server")
Server::~Server() = default;

void Server::start() {
  std::cout << "Server started on port " << mPort << std::endl;
  doAccept();
}

void Server::doAccept() {
  mAcceptor.async_accept(
      [this](const boost::system::error_code &ec, tcp::socket socket) {
        if (ec == boost::asio::error::eof) {
          std::cout << "Connection closed by peer" << std::endl;
        } else if (ec) {
          std::cerr << "Accept error: " << ec.message() << std::endl;
        } else {
          onAccept(std::move(socket));
          doAccept();
        }
      });
}

void Server::onAccept(tcp::socket socket) {
  std::cout << "New connection from "
            << socket.remote_endpoint().address().to_string() << ":"
            << socket.remote_endpoint().port() << '\n';

  std::make_shared<Session>(std::move(socket))->start();
}
} // namespace libmc::network