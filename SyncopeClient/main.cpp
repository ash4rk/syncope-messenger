#include <imgui.h>
#include "Networking/chat_protocol.h"
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
  Window window = Window();

  TCPClient client{"localhost", 6060};

  client.OnMessage = [&window](const std::string &message) {
    std::cout << "OnMessage" << message;
    switch (Syncopy::GetCommandName(message)) {
    case (Syncopy::Command::SHOUT): {
      ShoutMessage shoutMessage = ParseShout(message);
      window.AddMessage(shoutMessage.username + ": " + shoutMessage.body + "\n");
      break;
    }
    case (Syncopy::Command::WHISPER): {
      WhisperMessage whisperMessage = ParseWhisper(message);
      if (whisperMessage.result == "SUCCESS") {
        window.isLoggedIn = true;
      } else {
        window.loginErrorText = whisperMessage.body;
      }

      std::cout << "Get whisper message. result is:" << whisperMessage.result << " body is:" << whisperMessage.body << "\n";
      break;
    }
    default:
      break;
    }
  };

  std::thread t{[&client]() { client.Run(); }};

  window.Init();
  window.Loop([&client](const std::string &message) { client.Post(message); });

  // Terminate client
  client.Stop();
  t.join();
  return 0;
}
