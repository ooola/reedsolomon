cmake_minimum_required(VERSION 3.0)

project(reedsolomon)


enable_testing()

#add_definitions(-Wno-narrowing)


add_executable(rs main.cpp galois.cpp matrix.cpp rs.cpp util.cpp)

add_library(test_main OBJECT test_main.cpp)

add_executable(galois_test galois_test.cpp galois.cpp util.cpp $<TARGET_OBJECTS:test_main>)
add_test(NAME galois_test COMMAND galois_test)

add_executable(matrix_test matrix_test.cpp matrix.cpp galois.cpp util.cpp $<TARGET_OBJECTS:test_main>)
add_test(NAME matrix_test COMMAND matrix_test)

add_executable(rs_test rs_test.cpp rs.cpp matrix.cpp galois.cpp util.cpp $<TARGET_OBJECTS:test_main>)
add_test(NAME rs_test COMMAND rs_test)

set_target_properties(
    test_main 
    galois_test 
    matrix_test 
    rs_test
    PROPERTIES 
        CXX_STANDARD 11
        CMAKE_CXX_EXTENSIONS YES
)

# TODO figure out how to integrate Cmake and Cuda along with the native code version
#add_executable(grs rs.cu matrix.cpp galois.cpp util.cpp main.cpp )
#target_compile_options(grs PRIVATE $<$<COMPILE_LANGUAGE:CUDA>:-lstdc++ -DUSE_GPU>) 
#set_target_properties(
#    grs
#    PROPERTIES
#        CUDA_HOME /usr/lib/cuda
#)


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