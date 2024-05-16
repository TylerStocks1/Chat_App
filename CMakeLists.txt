cmake_minimum_required(VERSION 3.10)
project(ChatApp VERSION 1.0)

# Add server executable
add_executable(server src/server.cpp src/socket_utils.cpp)

# Add client executable
add_executable(client src/client.cpp src/socket_utils.cpp)

# Include the 'include' directory
include_directories(include)

# Set output directory for compiled binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
