cmake_minimum_required(VERSION 3.22)

project(Checkers)

file(GLOB src ./src/**/*.cpp ./src/**/*.hpp)

add_executable(Checkers ${src})

find_package(SFML 2 REQUIRED system window graphics network audio)

target_link_libraries(Checkers sfml-graphics sfml-audio)