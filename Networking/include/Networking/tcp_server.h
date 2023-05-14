#pragma once

#include "Networking/tcp_connection.h"
#include <boost/asio.hpp>
#include <optional>
#include <unordered_set>
#include <vector>

namespace Syncopy {
namespace io = boost::asio;
enum class IPV { V4, V6 };

class TCPServer {
  using OnJoinHandler = std::function<void(TCPConnection::pointer)>;
  using OnLeaveHandler = std::function<void(TCPConnection::pointer)>;
  using OnClientMessageHandler =
      std::function<void(std::string, TCPConnection::pointer)>;

public:
  TCPServer(IPV ipv, int port);

  int Run();
  void Broadcast(const std::string &message);
  void SendDirect(const TCPConnection::pointer &connection,
                  const std::string &message);
  void AuthorizeClient(std::string &login, std::string &password);

private:
  void startAccept();

public:
  OnJoinHandler OnJoin;
  OnLeaveHandler OnLeave;
  OnClientMessageHandler OnClientMessage;

private:
  IPV _ipVersion;
  int _port;

  io::io_context _ioContext;
  io::ip::tcp::acceptor _acceptor;
  std::optional<io::ip::tcp::socket> _socket;
  std::unordered_set<TCPConnection::pointer> _connections{};
};
} // namespace Syncopy
