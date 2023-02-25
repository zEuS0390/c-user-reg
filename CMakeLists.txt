cmake_minimum_required(VERSION 3.10)
project(registration LANGUAGES "CXX" VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

list(APPEND SRC_FILES
	${PROJECT_SOURCE_DIR}/src/main.cpp
	${PROJECT_SOURCE_DIR}/src/db.cpp
)

add_executable(registration ${SRC_FILES})
target_link_libraries(registration "${PROJECT_SOURCE_DIR}/libs/sqlite3/libsqlite3.a")
target_include_directories(registration PUBLIC "${PROJECT_SOURCE_DIR}/include" "${PROJECT_SOURCE_DIR}/libs/sqlite3")
