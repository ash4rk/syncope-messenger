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

namespace Syncopy {

class Window {
public:
  Window();
  GLFWwindow *Init();
  void Loop(std::function<void(const std::string& message)> onMessgeSend);
  void AddMessage(const std::string &message);

private:
public:
private:
  GLFWwindow *_window;
  std::string _messages = "";
};

} // namespace Syncopy
