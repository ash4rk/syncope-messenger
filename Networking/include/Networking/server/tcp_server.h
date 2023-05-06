#pragma once

#include "Networking/server/tcp_connection.h"
#include <boost/asio.hpp>
#include <vector>
#include <optional>
#include <unordered_set>

namespace Syncopy {
namespace io = boost::asio;
enum class IPV { V4, V6 };

class TCPServer {
  using OnJoinHandler = std::function<void(TCPConnection::pointer)>;
  using OnLeaveHandler = std::function<void(TCPConnection::pointer)>;
  using OnClientMessageHandler = std::function<void(std::string)>;

public:
  TCPServer(IPV ipv, int port);

  int Run();
  void Broadcast(const std::string &message);

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
}
