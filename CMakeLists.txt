cmake_minimum_required(VERSION 2.8.9)
project (LearningSnake)

include_directories(include)
#set(SOURCES src/main.cc src/Snake.cc)

file(GLOB SOURCES "src/*.cc")

add_executable(learning_snake ${SOURCES})
