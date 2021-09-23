cmake_minimum_required (VERSION 2.6)

add_definitions(-DRS_STATIC)

add_executable(rs main.cpp)

# detect operating system
message(STATUS "We are on a ${CMAKE_SYSTEM_NAME} system")
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    target_link_libraries(rs "-static")
else()
    target_link_libraries(rs )
endif()

enable_testing()

#add_test(alltests test/test.sh)
