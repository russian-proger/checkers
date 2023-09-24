cmake_minimum_required(VERSION 3.22)

project(Checkers)

file(GLOB src ./src/**/*.cpp ./src/**/*.hpp)
message(${src})
add_executable(Checkers ${src})
# add_executable(Checkers
#     Engine/State.cpp
#     Main/Main.cpp
# )

find_package(SFML 2 REQUIRED system window graphics network audio)

target_link_libraries(Checkers sfml-graphics sfml-audio)