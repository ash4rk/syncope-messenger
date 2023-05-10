#include "window.h"
#include "Networking/chat_protocol.h"



namespace Syncopy {

Window::Window() {};

GLFWwindow *Window::Init() {
  if (!glfwInit()) {
    //    return 1;
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
    // return 1;
  }
  glfwMakeContextCurrent(_window);
  glfwSwapInterval(1); // Enable vsync

  bool err = glewInit() != GLEW_OK;

  if (err) {
    fprintf(stderr, "Failed to initialize OpenGL loader!\n");
    //    return 1;
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

  void Window::Loop(std::function<void(const std::string& message)> onMessgeSend) {
  char chatInput[256] = {0};

  while (!glfwWindowShouldClose(_window)) {
    glfwPollEvents();
    glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT);

    // feed inputs to dear imgui, start new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::ShowDemoWindow();

    ImGui::Text("Chat here:");
    ImGui::SameLine();
    ImGui::Text("%s", _messages.c_str());

    if (ImGui::InputTextMultiline(
            "###text", chatInput, IM_ARRAYSIZE(chatInput),
            ImVec2(760, 40),
            ImGuiInputTextFlags_EnterReturnsTrue |
            ImGuiInputTextFlags_CtrlEnterForNewLine)) {

      onMessgeSend(SendSay(std::string(chatInput)));
      memset(chatInput, 0, sizeof(chatInput));
      ImGui::SetKeyboardFocusHere(0);
    }
      if (ImGui::Button("AUTH BUTTON")) {
        onMessgeSend("AUTH admin:admin\n");
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

} // namespace Syncopy
