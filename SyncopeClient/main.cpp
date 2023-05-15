#include "Networking/chat_protocol.h"
#include "Networking/tcp_client.h"
#include "bindings/imgui_impl_glfw.h"
#include "bindings/imgui_impl_opengl3.h"
#include "window.h"
#include <Log/log.h>
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <exception>
#include <imgui.h>
#include <iostream>
#include <ostream>
#include <string>
#include <thread>

// Initialize with glewInit()
#include <GL/glew.h>

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

using namespace Syncope;

int main() {
  Log::Init();

  Window window = Window();

  TCPClient client{"localhost", 6060};

  client.OnMessage = [&window](const std::string &message) {
    switch (GetCommandName(message)) {
    case (Command::SHOUT): {
      ShoutMessage shoutMessage = ParseShout(message);
      window.AddMessage(shoutMessage.username + ": " + shoutMessage.body +
                        "\n");
      break;
    }
    case (Command::WHISPER): {
      WhisperMessage whisperMessage = ParseWhisper(message);
      if (whisperMessage.result == "SUCCESS") {
        window.isLoggedIn = true;
      } else {
        window.loginErrorText = whisperMessage.body;
      }
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
