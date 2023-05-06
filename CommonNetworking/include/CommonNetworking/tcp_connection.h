#pragma once

#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <memory>


namespace Syncopy {
  using boost::asio::ip::tcp;
  class TCPConnection : public std::enable_shared_from_this<TCPConnection> {
  public:
    using pointer = std::shared_ptr<TCPConnection>;

    static pointer Create(boost::asio::io_context& ioContext) {
      return pointer(new TCPConnection(ioContext));
    }

    tcp::socket& Socket() { return _socket; }

    void Start();
  private:
    explicit TCPConnection(boost::asio::io_context& ioContext);

  private:
    tcp::socket _socket;
    std::string _message { "Hello, mr. Client!\n" };


  };
}
