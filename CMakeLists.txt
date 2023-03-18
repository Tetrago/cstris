cmake_minimum_required(VERSION 3.13)
project(cstris)

find_package(raylib CONFIG REQUIRED)

add_executable(cstris
    "src/board.cpp"
    "src/board.hpp"
    "src/dropper.cpp"
    "src/dropper.hpp"
    "src/main.cpp"
    "src/tetrimino.cpp"
    "src/tetrimino.hpp")

target_compile_features(cstris PRIVATE cxx_std_17)

target_link_libraries(cstris PRIVATE raylib)
target_include_directories(cstris PRIVATE "src")