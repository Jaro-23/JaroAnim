cmake_minimum_required(VERSION 3.20)

project(JaroAnim VERSION 1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Fetch content

include(FetchContent)

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG master
)

FetchContent_MakeAvailable(glm)

# Build library
file(GLOB_RECURSE SOURCES 
  "${PROJECT_SOURCE_DIR}/src/*.cpp"
)
add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${PROJECT_SOURCE_DIR}/headers
    ${glm_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/includes/headers
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  ${PROJECT_SOURCE_DIR}/includes/libs/libJaroViewer.so
  glm
)
