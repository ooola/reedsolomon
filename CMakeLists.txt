
cmake_minimum_required(VERSION 3.0)
#project (testexample) 

project(reedsolomon)


enable_testing()

#add_definitions(-Wno-narrowing)

add_executable(rs main.cpp galois.cpp matrix.cpp)

add_library(test_main OBJECT test_main.cpp)

add_executable(test1 test1.cpp $<TARGET_OBJECTS:test_main>)
add_test(NAME test1 COMMAND test1)

add_executable(test2 test2.cpp $<TARGET_OBJECTS:test_main>)
add_test(NAME test2 COMMAND test2 )

add_executable(galois_test galois_test.cpp galois.cpp $<TARGET_OBJECTS:test_main>)
add_test(NAME galois_test COMMAND galois_test)

add_executable(matrix_test matrix_test.cpp matrix.cpp galois.cpp $<TARGET_OBJECTS:test_main>)
add_test(NAME matrix_test COMMAND matrix_test)

add_executable(rs_test rs_test.cpp rs.cpp matrix.cpp galois.cpp $<TARGET_OBJECTS:test_main>)
add_test(NAME rs_test COMMAND rs_test)

set_target_properties(
    test_main 
    test1
    test2
    galois_test 
    matrix_test 
    rs_test
    PROPERTIES 
        CXX_STANDARD 11
        CMAKE_CXX_EXTENSIONS YES
)

#include_directories(../)

#set_target_properties(test1 PROPERTIES 
#    CXX_STANDARD 11
#    CMAKE_CXX_EXTENSIONS YES
#)
#
#set_target_properties(test2 PROPERTIES 
#    CXX_STANDARD 11
#    CMAKE_CXX_EXTENSIONS YES
#)