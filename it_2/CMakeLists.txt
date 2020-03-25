cmake_minimum_required(VERSION 3.8)

project(it_2)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(INC
   source/types.h
   source/single_proc.h
   source/multy_proc.h
   source/read_data.h
)

set(SRC
    #source/main.c
    #source/memory_work.c
    source/work_data.c
    source/single_proc.c
    source/multy_proc.c
#    source/process.c
)

add_library(single_proc STATIC source/single_proc.c)
add_library(multy_proc SHARED source/multy_proc.c)
add_executable(it_2
    ${INC}
    source/main.c
    ${SRC}
)
target_link_libraries(it_2 single_proc dl)

#add_executable(my_test
    #${INC}
    #source/test.cpp
    #${SRC})
#enable_testing()
#add_test(gtest ${EXECUTABLE_OUTPUT_PATH}/tests_gtest)
#add_definitions(-fprofile-arcs -ftest-coverage)
#target_link_libraries(my_test -fprofile-arcs)

target_include_directories(it_2
    PUBLIC
        "source"
)
#target_include_directories(my_test
    #PUBLIC
        #"include"
#)

#target_link_libraries(my_test ${GTEST_LIBRARIES} pthread)
