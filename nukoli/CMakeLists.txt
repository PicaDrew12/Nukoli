cmake_minimum_required(VERSION 3.28)
project(Nukoli LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# List all source files
set(NUKOLI_SRC
    src/Nukoli.cpp
    src/Global.cpp
    src/Rendering.cpp
    src/Sprite.cpp
    src/Malia.cpp
    src/Koge.cpp
    src/Utils.cpp
    src/Maisi.cpp
    src/Map.cpp
    src/Debug.cpp
        include/Save.h
        src/Save.cpp
)

# Create a static library from sources only
add_library(Nukoli STATIC ${NUKOLI_SRC} "src/Saisa.cpp" "include/Utils.h" "include/Map.h" "include/Debug.h")

# Include headers
target_include_directories(Nukoli PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# SFML dependency
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(SFML)

target_link_libraries(Nukoli PUBLIC SFML::Graphics SFML::Audio)