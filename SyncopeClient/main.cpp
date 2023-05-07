#include <exception>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include "Networking/client/tcp_client.h"
#include <string>
#include <thread>

using namespace Syncopy;

int main() {
  std::cout << "Hello, World! I am client!" << std::endl;
  try {
  TCPClient client{"localhost", 6060};

  client.OnMessage = [](const std::string &message) { std::cout << message; };

  std::thread t{[&client]() { client.Run(); }};



  while (true) {
    std::string message;
    getline(std::cin, message);

    if (message == "\\q") { break; }
    message += "\n";

    client.Post(message);
  }

  client.Stop();
  t.join();

  } catch (std::exception &e) {
  std::cerr << e.what() << std::endl;
  }
  return 0;
}
