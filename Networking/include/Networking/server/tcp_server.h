#pragma once

#include "Networking/server/tcp_connection.h"
#include <boost/asio.hpp>
#include <vector>


namespace Syncopy {
  enum class IPV {
    V4,
    V6
  };

  class TCPServer{

  public:
    TCPServer(IPV ipv, int port);

    int Run();
  private:
    void startAccept();
  private:
    IPV _ipVersion;
    int _port;

    boost::asio::io_context _ioContext;
    boost::asio::ip::tcp::acceptor _acceptor;

    std::vector<TCPConnection::pointer> _connections {};
  };
}
