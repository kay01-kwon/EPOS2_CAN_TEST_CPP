cmake_minimum_required(VERSION 2.8.11)
project(CAN_test)

# Executables for practice
add_executable (CAN_test src/CAN_test.cpp)
target_link_libraries (CAN_test)

add_executable (byte_test src/byte_test.cpp)
target_link_libraries (byte_test)
