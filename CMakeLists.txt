cmake_minimum_required(VERSION 3.1)
project(pi-adapter C)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS" ${CMAKE_C_FLAGS} -Wall -Wextra -O")

find_package(Threads REQUIRED)
find_package(aoip REQUIRED)

# pi-adapter
add_executable(pi-adapter src/pi-adapter.c)
target_link_libraries(pi-adapter Threads::Threads aoip::aoip)

