#pragma once

#include <functional>
#include <imgui.h>
#include <string>
#include "bindings/imgui_impl_glfw.h"
#include "bindings/imgui_impl_opengl3.h"

// Initialize with glewInit()
#include <GL/glew.h>

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

namespace Syncopy {

class Window {
public:
  Window();
  GLFWwindow *Init();
  void Loop(std::function<void()> onMessgeSend, std::string &last_message);

private:
public:
private:
  GLFWwindow *_window;
};
} // namespace Syncopy
