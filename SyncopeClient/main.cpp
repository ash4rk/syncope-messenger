#include <imgui.h>
#include "Networking/client/tcp_client.h"
#include "bindings/imgui_impl_glfw.h"
#include "bindings/imgui_impl_opengl3.h"
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <exception>
#include <iostream>
#include <string>
#include <thread>

// Initialize with glewInit()
#include <GL/glew.h>

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

using namespace Syncopy;

int main()
{
	// Setup window
	// glfwSetErrorCallback(glfw_error_callback); 
	if (!glfwInit())
		return 1;

		// Decide GL+GLSL versions
#if __APPLE__
	// GL 3.2 + GLSL 150
	const char *glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);		   // Required on Mac
#else
	// GL 3.0 + GLSL 130
	const char *glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

	// Create window with graphics context
	GLFWwindow *window = glfwCreateWindow(1280, 720, "Dear ImGui - Conan", NULL, NULL);
	if (window == NULL)
		return 1;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	bool err = glewInit() != GLEW_OK;

	if (err)
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return 1;
	}

	int screen_width, screen_height;
	glfwGetFramebufferSize(window, &screen_width, &screen_height);
	glViewport(0, 0, screen_width, screen_height);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT);

		// feed inputs to dear imgui, start new frame
    ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// render your GUI
		//ImGui::Begin("Triangle Position/Color");
    //		static float rotation = 0.0;
    //		ImGui::SliderFloat("rotation", &rotation, 0, 2 * PI);
    //    ImGui::End();
		// Render dear imgui into screen
		ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glfwSwapBuffers(window);
	}

	// Cleanup
  ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
  //############# End of GUI Part ###################

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
