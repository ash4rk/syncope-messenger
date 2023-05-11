cmake_minimum_required(VERSION 3.19)
project(SyncopeMessenger)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

add_subdirectory(Networking)
add_subdirectory(SyncopeClient)
add_subdirectory(SyncopeServer)
