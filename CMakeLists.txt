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
)

set(DIRECTORIES
    src/gameplay/characters
    src/gameplay/props
    src/io
    src/state
)

# Add the executable
add_executable(blackjack ${SOURCES} src/io/key_action.h)

target_include_directories(blackjack
  PRIVATE DIRECTORIES)

# Add build type options (Debug and Release)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)  # Default to Debug build if no type is specified
endif()

# Enable Debug Symbols
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  message("Building in Debug mode")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")  # Add the -g flag for debugging symbols
endif()

