#include "Networking/tcp_server.h"
#include <iostream>
#include <unordered_set>
#include <vector>

namespace Syncopy {
using boost::asio::ip::tcp;
TCPServer::TCPServer(IPV ipv, int port)
    : _ipVersion(ipv), _port(port),
      _acceptor(_ioContext,
                tcp::endpoint(ipv == IPV::V4 ? tcp::v4() : tcp::v6(), _port)) {}

int TCPServer::Run() {
  try {
    startAccept();
    _ioContext.run();
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }
  return 0;
}

void TCPServer::Broadcast(const std::string &message) {
  for (auto &connection : _connections) {
    connection->Post(message);
  }
}

void TCPServer::AuthorizeClient(std::string &login, std::string &pass) {}

void TCPServer::startAccept() {
  _socket.emplace(_ioContext);

  // asynchronously accept the connection
  _acceptor.async_accept(
      *_socket, [this](const boost::system::error_code &error) {
        auto connection = TCPConnection::Create(std::move(*_socket));
        if (OnJoin) {
          OnJoin(connection);
        }

        _connections.insert(connection);

        if (!error) {
          connection->Start(
              [this, connection](const std::string &message) {
                // if (_authorized_connections.find(connection) ==
                // _authorized_connections.end())
                //   {
                //     AuthorizeClient(std::string &login, std::string &pass)
                //   }
                if (OnClientMessage)
                  OnClientMessage(message, connection);
              },
              [&, weak = std::weak_ptr(connection)] {
                if (auto shared = weak.lock();
                    shared && _connections.erase(shared)) {
                  if (OnLeave)
                    OnLeave(shared);
                }
              });
        }

        startAccept();
      });
}
} // namespace Syncopy
