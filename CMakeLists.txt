cmake_minimum_required(VERSION 3.10)

project(registration LANGUAGES "CXX" VERSION 1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(registration ${CMAKE_SOURCE_DIR}/src/main.cpp ${CMAKE_SOURCE_DIR}/src/db.cpp)

include_directories(${CMAKE_SOURCE_DIR}/include)

target_link_libraries(registration ${CMAKE_SOURCE_DIR}/lib/libsqlite3.a)
