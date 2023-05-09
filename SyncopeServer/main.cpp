#include "Networking/tcp_connection.h"
#include <Networking/tcp_server.h>
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <iostream>
#include <ostream>

enum string_code { AUTH, SEND, BAD_PATH };

string_code hashit(std::string const &inString) {
  if (inString == "AUTH")
    return AUTH;
  if (inString == "SEND")
    return SEND;
  return BAD_PATH;
}

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
    std::string route;
    std::string username;
    getline(iss, username, '/');
    std::cout << "From username: " << username << std::endl;
    getline(iss, route, '/');
    std::cout << "Route is: " << route << std::endl;

    switch (hashit(route)) {
    case AUTH: {
      std::cout << "Authorization attempt: " << std::endl;
      std::string login;
      std::string password;
      getline(iss >> std::ws, login, ':');
      getline(iss >> std::ws, password, ':');
      // AUTH here
      std::cout << "login:" << login << " password:" << password << std::endl;
      if (login == "admin" && password == "admin") {
        std::cout << "Successful authorization" << std::endl;
        client->SetAuth(true);
      } else {
        std::cout << "WRONG CREDENTIALS!" << std::endl;
      }
      break;
    }
    case SEND: {
      // Check if Authorized if not return
      if (!client->IsAuth()) {
        std::cout << "Has not AUTH!" << std::endl;
        return;
      }
      std::string messageBody;
      getline(iss, messageBody);

      std::cout << "Trying to broadcast message: \"" << messageBody << "\"" << std::endl;

      // Send message to clients
      server.Broadcast(messageBody + "\n");
      break;
    }
    case BAD_PATH: {
      std::cout << "BAD ROUTE" << std::endl;
      break;
    }
    }
  };

  server.Run();

  return 0;
}
