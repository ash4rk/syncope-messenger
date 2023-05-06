#include <CommonNetworking/Base.h>
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <iostream>

using boost::asio::ip::tcp;

int main() {
  std::cout << "Hello, World! I am server!" << std::endl;
  try {
    boost::asio::io_context io_context;

    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 6060));

    while(true) {
      std::cout << "Accepting connections on port 6060!" << std::endl;

      tcp::socket socket(io_context);
      acceptor.accept(socket);

      std::cout << "Client connected! Sending message." << std::endl;
      std::string hello_message = "Hello, mr. client\n";
      boost::system::error_code error;

      boost::asio::write(socket, boost::asio::buffer(hello_message), error);
    }
  } catch (std::exception& e) {
    std::cerr <<  e.what() << std::endl;
  }
  return 0;
}
