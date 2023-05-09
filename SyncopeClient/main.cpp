#include <imgui.h>
#include "Networking/tcp_client.h"
#include "bindings/imgui_impl_glfw.h"
#include "bindings/imgui_impl_opengl3.h"
#include "window.h"
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <string>
#include <thread>

// Initialize with glewInit()
#include <GL/glew.h>

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

using namespace Syncopy;

int main() {
  //Window window = Window();
  Window window = Window();

  TCPClient client{"localhost", 6060};

  client.OnMessage = [&window](const std::string &message) {
    std::cout << message;
    window.AddMessage(message);
  };

  std::thread t{[&client]() { client.Run(); }};

   window.Init();
   window.Loop([&client](const std::string &message) { client.Post(message); });

  // Terminate client
  client.Stop();
  t.join();
  return 0;
}
