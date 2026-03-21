cmake_minimum_required(VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(planets VERSION 1.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/)

add_subdirectory(lib)
file(GLOB_RECURSE SOURCES 
  "${PROJECT_SOURCE_DIR}/examples/${PROJECT_NAME}/src/*.cpp"
)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
  PRIVATE
  ${PROJECT_SOURCE_DIR}/examples/${PROJECT_NAME}/headers
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  JaroAnim
)

if (PROJECT_IS_TOP_LEVEL AND UNIX)
  # Create symlink to compile_commands.json for IDE to pick it up
  execute_process(
    COMMAND ${CMAKE_COMMAND} -E create_symlink
      ${CMAKE_BINARY_DIR}/compile_commands.json
      ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
  )
endif()
