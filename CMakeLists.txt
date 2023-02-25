cmake_minimum_required(VERSION 3.10)
project(registration LANGUAGES C CXX VERSION 1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(LIBS_DIR "${PROJECT_SOURCE_DIR}/libs")
set(SQLITE_LIB_NAME "sqlite-amalgamation-3410000")
set(SQLITE_LIB_LINK "https://www.sqlite.org/2023/${SQLITE_LIB_NAME}.zip")

if (NOT EXISTS "${PROJECT_SOURCE_DIR}/libs/sqlite3")
	message("Downloading '${SQLITE_LIB_NAME}' library")

	# Download the library
	file(DOWNLOAD "${SQLITE_LIB_LINK}" "${LIBS_DIR}/${SQLITE_LIB_NAME}.zip" SHOW_PROGRESS)

	# Extract the downloaded zip file
	file(ARCHIVE_EXTRACT INPUT "${LIBS_DIR}/${SQLITE_LIB_NAME}.zip" DESTINATION "${LIBS_DIR}/")

	# Rename the extracted folder
	file(RENAME "${LIBS_DIR}/${SQLITE_LIB_NAME}" "${PROJECT_SOURCE_DIR}/libs/sqlite3")

	# Delete the zip file
	file(REMOVE "${LIBS_DIR}/${SQLITE_LIB_NAME}.zip")
else()
	message(WARNING "'${SQLITE_LIB_NAME}' library already exist.")
endif()

list(APPEND SRC_FILES "${PROJECT_SOURCE_DIR}/src/main.cpp" "${PROJECT_SOURCE_DIR}/src/db.cpp")

if (EXISTS "${PROJECT_SOURCE_DIR}/libs/sqlite3")
	add_library(sqlite3 "${PROJECT_SOURCE_DIR}/libs/sqlite3/sqlite3.c")
	set_target_properties(sqlite3 PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/libs/sqlite3")
else()
	message(FATAL_ERROR "'${SQLITE_LIB_NAME}' library doesn't exist.")
endif()

add_executable(registration ${SRC_FILES})
target_link_libraries(registration "${PROJECT_SOURCE_DIR}/libs/sqlite3/libsqlite3.a")
target_include_directories(registration PUBLIC "${PROJECT_SOURCE_DIR}/include" "${PROJECT_SOURCE_DIR}/libs/sqlite3")

