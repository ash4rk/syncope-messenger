#include "Networking/server/tcp_connection.h"
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <Networking/server/tcp_server.h>
#include <iostream>

int main() {
  std::cout << "Hello, World! I am server!" << std::endl;

  Syncopy::TCPServer server {Syncopy::IPV::V4, 6060};

  server.OnJoin = [](Syncopy::TCPConnection::pointer server) {
    std::cout << "User has joined the server: " << server->GetUsername() << std::endl;
  };

  server.OnLeave = [](Syncopy::TCPConnection::pointer server) {
    std::cout << "User has left the server: " << server->GetUsername() << std::endl;
  };

  server.OnClientMessage = [&server](const std::string& message) {
    // Parse the message

    // Send message to client
    server.Broadcast(message);
  };

  server.Run();

  return 0;
}
