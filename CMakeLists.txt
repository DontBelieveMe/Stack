cmake_minimum_required(VERSION 2.6)
project(stack)

set(srcdir ${PROJECT_SOURCE_DIR}/source)

set(source 
    ${srcdir}/stack.c 
    ${srcdir}/parse.c 
    ${srcdir}/stacky.c
    ${srcdir}/common/string.c
    ${srcdir}/common/list.c )
    
include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(stack ${source})