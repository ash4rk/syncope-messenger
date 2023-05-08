#pragma once

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

namespace Syncopy {

class Window {
public:
  Window();
  void Init();
  void Loop();

private:


public:


private:
  GLFWwindow *window;
};
} // namespace Syncopy
