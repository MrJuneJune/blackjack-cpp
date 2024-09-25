cmake_minimum_required(VERSION 3.10)

# Export compile commands (useful for LSP tools)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_OSX_ARCHITECTURES "arm64")

# Set the project name
project(BlackjackGame)

# Include directories for headers
include_directories(src)

# Source files
set(SOURCES
    main.cpp
    src/gameplay/characters/player.cpp
    src/gameplay/props/deck.cpp
    src/state/game.cpp
    src/utils/loggers.cpp
    src/utils/helpers.cpp
)

set(DIRECTORIES
    src/gameplay/characters
    src/gameplay/props
    src/io
    src/state
    src/utils
)

## Cardnal sin comments: Add below if I want to make an actual game from it using glfw and openGL as a practice I guess.
# Ignore warning
#add_definitions(-DGL_SILENCE_DEPRECATION)

## Third Party 
# # glfw
# add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/glfw)
# 
# # Find OpenGL (required by GLFW)
# find_package(OpenGL REQUIRED)
# find_package(GLEW REQUIRED)
# 
# # Find libwebp
# find_library(WEBP_LIBRARY webp REQUIRED)
# 
# # Include WebP headers (adjust the path to where libwebp is installed, if needed)
# include_directories("/usr/include/webp")
# 

add_executable(blackjack ${SOURCES})

# target_link_libraries(blackjack PRIVATE glfw OpenGL::GL GLEW::GLEW ${WEBP_LIBRARY})

# Include directories for your source files
# target_include_directories(blackjack PRIVATE ${DIRECTORIES} ${GLEW_INCLUDE_DIRS})
target_include_directories(blackjack PRIVATE ${DIRECTORIES})


## Debugger stuff
# Add build type options (Debug and Release)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)  # Default to Debug build if no type is specified
endif()

# Enable Debug Symbols
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  message("Building in Debug mode")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")  # Add the -g flag for debugging symbols
endif()

