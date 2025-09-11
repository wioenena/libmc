#include <boost/asio.hpp>
#include <network/server.hpp>


using namespace libmc::network;

int main() {
  boost::asio::io_context ioContext;
  Server server(ioContext, 25565);
  server.start();
  ioContext.run();
  return 0;
}