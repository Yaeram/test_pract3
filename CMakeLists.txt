cmake_minimum_required(VERSION 3.21)
project(Crypt)

link_libraries("-static")
set(CMAKE_CXX_STANDARD 17)

add_executable(Crypt main.cpp)
include_directories(crypto_utils_lib)
add_subdirectory(crypto_utils_lib)

target_link_libraries(Crypt crypto_utils_lib)
add_subdirectory(Google_tests)