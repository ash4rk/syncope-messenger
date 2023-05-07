cmake_minimum_required(VERSION 3.19)
project(SyncopeMessenger)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

#### Set up Conan and build dependencies #### https://github.com/conan-io/cmake-conan ##################################
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake"
            EXPECTED_HASH SHA256=396e16d0f5eabdc6a14afddbcfff62a54a7ee75c6da23f32f7a31bc85db23484
            TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)
set(CONAN_SYSREQUIRES_MODE "enabled")
conan_cmake_configure(REQUIRES
        spdlog/1.9.2
        boost/1.77.0
        glfw/3.3.6
        glew/2.2.0
        imgui/1.89.4        
        GENERATORS cmake cmake_paths cmake_find_package)
conan_cmake_autodetect(settings)
conan_cmake_install(PATH_OR_REFERENCE .
        BUILD missing
        REMOTE conancenter
        SETTINGS ${settings})
########################################################################################################################

add_subdirectory(Networking)
add_subdirectory(SyncopeClient)
add_subdirectory(SyncopeServer)
