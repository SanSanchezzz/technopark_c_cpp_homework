cmake_minimum_required(VERSION 3.8)

project(it_1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -Wall -ggdb3")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -Wall -ggdb3")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Werror -ggdb3")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(INC
   include/types.h
)

set(SRC
    #source/main.c
    source/memory_work.c
    source/read_data.c
    source/process.c
)

add_executable(it_1
    ${INC}
    source/main.c
    ${SRC}
)

add_executable(my_test
    ${INC}
    source/test.cpp
    ${SRC})

target_include_directories(it_1
    PUBLIC
        "include"
)
target_include_directories(my_test
    PUBLIC
        "include"
)

target_link_libraries(my_test ${GTEST_LIBRARIES} pthread)
