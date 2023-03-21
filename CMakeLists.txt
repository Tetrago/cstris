cmake_minimum_required(VERSION 3.13)
project(cstris)

find_package(raylib CONFIG REQUIRED)

add_library(cstris STATIC
    "libs/cstris/board.cpp"
    "libs/cstris/board.hpp"
    "libs/cstris/dropper.cpp"
    "libs/cstris/dropper.hpp"
    "libs/cstris/game.cpp"
    "libs/cstris/game.hpp"
    "libs/cstris/tetrimino.cpp"
    "libs/cstris/tetrimino.hpp")

target_compile_features(cstris PUBLIC cxx_std_17)
target_include_directories(cstris PUBLIC "libs/cstris")

add_library(cythe STATIC
    "libs/cythe/cythe.hpp"
    "libs/cythe/cythe.cpp")

target_compile_features(cythe PUBLIC cxx_std_17)
target_include_directories(cythe PUBLIC "libs/cythe")

add_executable(rlib "extras/rlib/main.cpp")

target_link_libraries(rlib PRIVATE cstris raylib)