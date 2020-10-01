cmake_minimum_required(VERSION 3.11)

project(somecode)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)
find_package(GTest CONFIG REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads GTest::gmock_main)

add_custom_target(run_executable COMMAND ${PROJECT_NAME})
