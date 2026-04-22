cmake_minimum_required(VERSION 3.28)
project(NukoliProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add the engine and game subdirectories
add_subdirectory(nukoli)
add_subdirectory(game)