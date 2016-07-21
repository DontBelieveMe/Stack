cmake_minimum_required(VERSION 2.6)
project(stack)

set(source stack.c parse.c stacky.c)
include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(stack ${source})