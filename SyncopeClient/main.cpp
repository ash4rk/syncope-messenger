#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>

using boost::asio::ip::tcp;

int main() {
  std::cout << "Hello, World! I am client!" << std::endl;
  try{
    boost::asio::io_context io_context;

    tcp::resolver resolver { io_context };
    auto endpoints = resolver.resolve("127.0.0.1", "6060");

    tcp::socket socket { io_context };
    boost::asio::connect(socket, endpoints);

    while(true) {
      // Listen for messages
      std::array<char, 128> buf {};
      boost::system::error_code error;

      size_t len = socket.read_some(boost::asio::buffer(buf), error);

      if (error == boost::asio::error::eof) {
        // Clean connection cut off
        break;
      } else if (error) {
        throw boost::system::system_error(error);
      }
      std::cout.write(buf.data(), len);
    }
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
