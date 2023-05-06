#include "CommonNetworking/tcp_connection.h"
#include <boost/asio/write.hpp>
#include <boost/operators.hpp>
#include <boost/system/detail/error_code.hpp>
#include <iostream>

namespace Syncopy {

  TCPConnection::TCPConnection(boost::asio::io_context &ioContext) : _socket(ioContext) {  }

  void TCPConnection::Start() {
    auto strongThis = shared_from_this();

    boost::asio::async_write(_socket, boost::asio::buffer(_message), [strongThis](const boost::system::error_code& error, size_t bytesTranferred){
      if (error) {
        std::cout << "Failed to send message!\n";
      } else {
        std::cout << "Sent " << bytesTranferred << " bytes of data!\n";
      }
    });
  }
} // namespace Syncopy
