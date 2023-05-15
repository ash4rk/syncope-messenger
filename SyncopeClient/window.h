#pragma once

#include <imgui.h>
#include "bindings/imgui_impl_glfw.h"
#include "bindings/imgui_impl_opengl3.h"
#include <functional>
#include <string>

// Initialize with glewInit()
#include <GL/glew.h>

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

namespace Syncope {

class Window {
public:
  Window();
  GLFWwindow *Init();
  void Loop(std::function<void(const std::string &message)> onPostMessage);
  void AddMessage(const std::string &message);

private:
  void logInWindow(std::function<void(const std::string &login)> onLogIn);
  void chatWindow(std::function<void(const std::string &login)> onSendSay);

public:
  bool isLoggedIn = false;
  std::string loginErrorText = "";

private:
  GLFWwindow *_window;
  std::string _messages = "";
  char _login[32] = {};
  char _password[32] = {};
  char _chatInput[256] = {};
};

} // namespace Syncope
