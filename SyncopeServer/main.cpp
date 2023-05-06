#include <CommonNetworking/Base.h>
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <CommonNetworking/tcp_server.h>
#include <iostream>

using boost::asio::ip::tcp;

int main() {
  std::cout << "Hello, World! I am server!" << std::endl;

  Syncopy::TCPServer server {Syncopy::IPV::V4, 6060};

  server.Run();

  return 0;
}
