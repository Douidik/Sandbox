project(SandboxEngine
  DESCRIPTION "Custom voxel game engine used in the sandbox game"
  LANGUAGES CXX)

project(SandboxGame
  DESCRIPTION "Open-Source sandbox game written in C++20 heavily inspired by Minecraft"
  LANGUAGES CXX)

# Temporary enable the debugging mode
set(CMAKE_BUILD_TYPE Debug)

# The project use C++20
set(CMAKE_CXX_STANDARD 20)
# For LSP symbol recognition
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Custom output directory for libraries and binaries
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/)

# Setup dependencies management through conan
set(CONAN_BUILD_INFO_FILEPATH cmake/conanbuildinfo.cmake)

if(EXISTS ${CONAN_BUILD_INFO_FILEPATH})
  include(${CONAN_BUILD_INFO_FILEPATH})
  conan_basic_setup()
else()
  message(FATAL_ERROR "conanbuildinfo.cmake is not created run \"conan install .. --build=missing\" inside the cmake folder")
endif()

# Meta detection
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
  add_compile_definitions(SBX_WINDOWS_OS)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin") # Darwin = mac os
  add_compile_definitions(SBX_MAC_OS)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  add_compile_definitions(SBX_LINUX_OS)
else()
  message(FATAL_ERROR "Sandbox is not yet compatible with ${CMAKE_SYSTEM_NAME}")
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
  add_compile_definitions(SBX_RELEASE_MODE)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  add_compile_definitions(SBX_DEBUG_MODE)
else()
  message(WARNING "Unknown build type ${CMAKE_BUILD_TYPE} defaulted to Release mode")
  add_compile_definitions(SBX_RELEASE_MODE)
endif()

add_subdirectory(src/SandboxEngine)
add_subdirectory(src/SandboxGame)

include_directories(src/)
