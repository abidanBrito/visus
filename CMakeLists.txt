cmake_minimum_required(VERSION 3.16)

project(
  visus
  VERSION 0.0.1
  DESCRIPTION "GPU-based Direct Volume Renderer"
  HOMEPAGE_URL "https://github.com/abidanBrito/visus"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compilation flags
if(MSVC)
  # NOTE(abi): MSVC is picky with extenal header files. This holds specially
  # true for strict warning policies. In the worst case-scenario this can lead
  # to unsuccesful builds. We have no intention of debugging system &
  # third-party headers, so let's disable warnings for them altogether.
  set(COMPILER_FLAGS_COMMON
      "/W4 /WX /FC /experimental:external /external:anglebrackets /external:W0")
  
  # Optimization & debug symbols
  set(COMPILER_FLAGS_DEBUG "/Od /Zi")
  set(COMPILER_FLAGS_RELEASE "/O2")
else()
  message("[INFO]: Compiler is not MSVC. You might want to add flags for it.")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(COMPILER_FLAGS "${COMPILER_FLAGS_COMMON} ${COMPILER_FLAGS_DEBUG}")
else()
  set(COMPILER_FLAGS "${COMPILER_FLAGS_COMMON} ${COMPILER_FLAGS_RELEASE}")
endif()

# IMPORTANT(abi): 'CMAKE_CXX_FLAGS' is a global variable, so given multiple
# targets it's probably not a great idea to set it this way.
# https://www.foonathan.net/2018/10/cmake-warnings/
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILER_FLAGS}")

# Targets output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

# Installation directory
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX
      "${CMAKE_SOURCE_DIR}/bin"
      CACHE PATH "Setting the install directory to ./bin" FORCE)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory("src")
