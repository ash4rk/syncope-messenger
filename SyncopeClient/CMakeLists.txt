cmake_minimum_required(VERSION 3.19)
project(SyncopeClient)

set(CMAKE_CXX_STANDARD 20)

find_package(imgui CONFIG)
find_package(glfw3 CONFIG)
find_package(glew CONFIG)

add_executable(${PROJECT_NAME} 
		main.cpp
		window.cpp
		window.h
                bindings/imgui_impl_glfw.cpp
                bindings/imgui_impl_opengl3.cpp
                bindings/imgui_impl_glfw.h
                bindings/imgui_impl_opengl3.h)		

target_compile_definitions(${PROJECT_NAME}
	PUBLIC 
	IMGUI_IMPL_OPENGL_LOADER_GLEW
)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		Networking
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		Networking
		imgui::imgui 
		GLEW::glew_s 
		glfw::glfw
)
