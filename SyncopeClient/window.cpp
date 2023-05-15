#include "window.h"
#include "Networking/chat_protocol.h"
#include <iostream>

namespace Syncope {

Window::Window(){};

GLFWwindow *Window::Init() {
  if (!glfwInit()) {
    throw std::invalid_argument("Failed to initialize GLFW library");
  }

  // Decide GL+GLSL versions
#if __APPLE__
  // GL 3.2 + GLSL 150
  const char *glsl_version = "#version 150";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on Mac
#else
  // GL 3.0 + GLSL 130
  const char *glsl_version = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+
  // only glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 3.0+ only
#endif

  // Create _window with graphics context
  _window = glfwCreateWindow(1280, 720, "Syncope Messenger", NULL, NULL);
  if (_window == NULL) {
    throw std::invalid_argument("_window not initialized");
  }
  glfwMakeContextCurrent(_window);
  glfwSwapInterval(1); // Enable vsync

  bool err = glewInit() != GLEW_OK;

  if (err) {
    throw std::invalid_argument("Failed to initialize OpenGL loader");
  }

  int screen_width, screen_height;
  glfwGetFramebufferSize(_window, &screen_width, &screen_height);
  glViewport(0, 0, screen_width, screen_height);

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForOpenGL(_window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);
  // Setup Dear ImGui style
  ImGui::StyleColorsDark();

  return _window;
}

void Window::Loop(
    std::function<void(const std::string &message)> onPostMessage) {

  while (!glfwWindowShouldClose(_window)) {
    glfwPollEvents();
    glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Feed inputs to dear imgui, start new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Build New Windows Here
    if (!isLoggedIn) {
      logInWindow(onPostMessage);

    } else {
      chatWindow(onPostMessage);
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    int display_w, display_h;
    glfwGetFramebufferSize(_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glfwSwapBuffers(_window);
  }

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(_window);
  glfwTerminate();
}

void Window::AddMessage(const std::string &message) { _messages += message; }

void Window::logInWindow(
    std::function<void(const std::string &password)> onLogIn) {
  ImGui::Text("Login:");
  ImGui::SameLine();
  ImGui::InputText("##login", _login, 32);
  ImGui::Text("Password:");
  ImGui::SameLine();
  ImGui::InputText("##password", _password, 32,
                   ImGuiInputTextFlags_Password |
                       ImGuiInputTextFlags_CharsNoBlank);
  if (ImGui::Button("Login")) {
    onLogIn(SendAuth(_login, _password));
  }
  ImGui::Text("%s", loginErrorText.c_str());
}

void Window::chatWindow(
    std::function<void(const std::string &login)> onSendSay) {
  ImGui::Text("Chat here:");
  ImGui::SameLine();
  ImGui::Text("%s", _messages.c_str());
  if (ImGui::InputTextMultiline("###text", _chatInput, IM_ARRAYSIZE(_chatInput),
                                ImVec2(760, 40),
                                ImGuiInputTextFlags_EnterReturnsTrue |
                                    ImGuiInputTextFlags_CtrlEnterForNewLine) &&
      strlen(_chatInput) != 0) {

    onSendSay(SendSay(std::string(_chatInput)));
    memset(_chatInput, 0, sizeof(_chatInput));
    ImGui::SetKeyboardFocusHere(-1);
  }
}

} // namespace Syncope
