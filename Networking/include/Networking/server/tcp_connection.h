#pragma once

#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <memory>


namespace Syncopy {
  using boost::asio::ip::tcp;
  namespace io = boost::asio;
  class TCPConnection : public std::enable_shared_from_this<TCPConnection> {
  public:
    using pointer = std::shared_ptr<TCPConnection>;

    static pointer Create(io::ip::tcp::socket&& socket) {
      return pointer(new TCPConnection(std::move(socket)));
    }

    tcp::socket& Socket() { return _socket; }

    void Start();
  private:
    explicit TCPConnection(io::ip::tcp::socket&& socket);

  private:
    tcp::socket _socket;
    std::string _message { "Hello, mr. Client!\n" };
  };
}
