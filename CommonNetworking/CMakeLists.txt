cmake_minimum_required(VERSION 3.19)
project(CommonNetworking)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES src/* src/*/* src/*/*/*)
file(GLOB H_FILES "src/*.h")
file(GLOB CPP_FILES "src/*.cpp")
file(GLOB CommonNetworking "include/CommonNetworking/*.*")
file(GLOB INCLUDE "include/*.*/*.*/*.*")

add_library(${PROJECT_NAME} ${H_FILES} ${CPP_FILES} ${CommonNetworking} ${INCLUDE} ${SOURCES})

target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
