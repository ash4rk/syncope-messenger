#include "Log/log.h"
#include "Networking/chat_protocol.h"
#include "Networking/tcp_connection.h"
#include <Networking/tcp_server.h>
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <iostream>
#include <ostream>

int main() {
  Syncopy::Log::Init();

  Syncopy::TCPServer server{Syncopy::IPV::V4, 6060};

  server.OnJoin = [](Syncopy::TCPConnection::pointer server) {
    SYNCOPE_INFO("User {0} has joined the server", server->GetUsername());
  };

  server.OnLeave = [](Syncopy::TCPConnection::pointer server) {
    SYNCOPE_INFO("User {0} has left the server", server->GetUsername());
  };

  server.OnClientMessage = [&server](const std::string &message,
                                     Syncopy::TCPConnection::pointer client) {
    // Parse the message
    std::istringstream iss(message);

    switch (Syncopy::GetCommandName(message)) {
    case Syncopy::Command::AUTH: {
      SYNCOPE_TRACE("Authorization attempt");
      Syncopy::AuthMessage credentials = Syncopy::ParseAuth(message);
      if (credentials.login == "admin" && credentials.password == "admin") {
        server.SendDirect(client, Syncopy::SendWhisper("SUCCESS", ""));
        client->SetAuth(true);
      } else {
        server.SendDirect(
            client,
            Syncopy::SendWhisper("ERROR", "Invalid user name or password "));
      }
      break;
    }
    case Syncopy::Command::SAY: {
      // Check if Authorized if not return
      if (!client->IsAuth()) {
        return;
      }
      Syncopy::SayMessage sayMessage = Syncopy::ParseSay(message);
      // Send message to clients
      server.Broadcast(
          Syncopy::SendShout(client->GetUsername(), sayMessage.body));
      break;
    }
    default: {
      break;
    }
    }
  };

  server.Run();

  return 0;
}
