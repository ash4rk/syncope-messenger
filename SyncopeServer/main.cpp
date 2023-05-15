#include "Log/log.h"
#include "Networking/chat_protocol.h"
#include "Networking/tcp_connection.h"
#include <Networking/tcp_server.h>
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <iostream>
#include <ostream>

using namespace Syncope;

int main() {
  Syncope::Log::Init();

  Syncope::TCPServer server{Syncope::IPV::V4, 6060};

  server.OnJoin = [](Syncope::TCPConnection::pointer server) {
    SYNCOPE_INFO("User {0} has joined the server", server->GetUsername());
  };

  server.OnLeave = [](Syncope::TCPConnection::pointer server) {
    SYNCOPE_INFO("User {0} has left the server", server->GetUsername());
  };

  server.OnClientMessage = [&server](const std::string &message,
                                     TCPConnection::pointer client) {
    // Parse the message
    std::istringstream iss(message);

    switch (GetCommandName(message)) {
    case Command::AUTH: {
      SYNCOPE_TRACE("Authorization attempt");
      AuthMessage credentials = ParseAuth(message);
      if (credentials.login == "admin" && credentials.password == "admin") {
        server.SendDirect(client, Syncope::SendWhisper("SUCCESS", ""));
        client->SetAuth(true);
      } else {
        server.SendDirect(
            client, SendWhisper("ERROR", "Invalid user name or password "));
      }
      break;
    }
    case Command::SAY: {
      // Check if Authorized if not return
      if (!client->IsAuth()) {
        return;
      }
      SayMessage sayMessage = Syncope::ParseSay(message);
      // Send message to clients
      server.Broadcast(SendShout(client->GetUsername(), sayMessage.body));
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
