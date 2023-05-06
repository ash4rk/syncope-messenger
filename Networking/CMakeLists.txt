cmake_minimum_required(VERSION 3.19)
project(Networking)

set(CMAKE_CXX_STANDARD 20)

find_package(spdlog REQUIRED)
find_package(Boost 1.77.0 REQUIRED)

file(GLOB SOURCES src/* src/*/* src/*/*/*)
file(GLOB H_FILES "src/*.h")
file(GLOB CPP_FILES "src/*.cpp")
file(GLOB Networking "include/Networking/*.*")
file(GLOB INCLUDE "include/*.*/*.*/*.*")

add_library(${PROJECT_NAME} ${H_FILES} ${CPP_FILES} ${Networking} ${INCLUDE} ${SOURCES})

target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
		spdlog::spdlog
		Boost::boost		
)

target_link_libraries(${PROJECT_NAME}
#	PUBLIC
#		spdlog::spdlog
	PRIVATE		
		Boost::boost
		spdlog::spdlog		
)
