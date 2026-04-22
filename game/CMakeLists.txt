cmake_minimum_required(VERSION 3.28)
project(Game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(Game
    "src/main.cpp"
)

# Link to the Nukoli engine library
target_link_libraries(Game PRIVATE Nukoli)

# -----------------------------------------------------------------------
# Clear and re-copy the assets folder next to the executable after every
# build.
#
# Step 1: remove_directory wipes the old assets/ folder so deleted or
#         renamed source assets don't linger in the output.
# Step 2: copy_directory copies game/assets/ Å® <exe dir>/assets/
#
# $<TARGET_FILE_DIR:Game> resolves at build time, so this works for
# Visual Studio (bin/Debug, bin/Release) and Ninja/Make (bin/) alike.
# -----------------------------------------------------------------------
add_custom_command(TARGET Game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove_directory
        "$<TARGET_FILE_DIR:Game>/assets"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:Game>/assets"
    COMMENT "Refreshing assets folder next to executable"
)