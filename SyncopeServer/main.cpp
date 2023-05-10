#include "Networking/chat_protocol.h"
#include "Networking/tcp_connection.h"
#include <Networking/tcp_server.h>
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <iostream>
#include <ostream>

int main() {
  std::cout << "Hello, World! I am server!" << std::endl;

  Syncopy::TCPServer server{Syncopy::IPV::V4, 6060};

  server.OnJoin = [](Syncopy::TCPConnection::pointer server) {
    std::cout << "User has joined the server: " << server->GetUsername()
              << std::endl;
  };

  server.OnLeave = [](Syncopy::TCPConnection::pointer server) {
    std::cout << "User has left the server: " << server->GetUsername()
              << std::endl;
  };

  server.OnClientMessage = [&server](const std::string &message,
                                     Syncopy::TCPConnection::pointer client) {
    // Parse the message
    std::istringstream iss(message);

    switch (Syncopy::GetCommandName(message)) {
    case Syncopy::Command::AUTH: {
      std::cout << "Authorization attempt: " << std::endl;
      Syncopy::AuthMessage credentials = Syncopy::ParseAuth(message);
      if (credentials.login == "admin" && credentials.password == "admin") {
        std::cout << "Successful authorization" << std::endl;
        client->SetAuth(true);
      }
      else {
        std::cout << "WRONG CREDENTIALS!" << std::endl;
      }
      break;
    }
    case Syncopy::Command::SAY: {
      // Check if Authorized if not return
      if (!client->IsAuth()) {
        std::cout << "Has not AUTH!" << std::endl;
        return;
      }
      Syncopy::SayMessage sayMessage = Syncopy::ParseSay(message);
      std::cout << "Trying to broadcast message: \"" << sayMessage.body << "\"" << std::endl;

      // Send message to clients
      //      server.Broadcast(messageBody + "\n");
      break;
    }
    case Syncopy::Command::BAD_PATH: {
      std::cout << "BAD ROUTE" << std::endl;
      break;
    }
    }
  };

  server.Run();

  return 0;
}
