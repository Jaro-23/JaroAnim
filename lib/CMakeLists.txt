cmake_minimum_required(VERSION 3.20)

project(JaroAnim VERSION 1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Build library
file(GLOB_RECURSE SOURCES 
  "${PROJECT_SOURCE_DIR}/src/*.cpp"
)
add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${PROJECT_SOURCE_DIR}/headers
    ${PROJECT_SOURCE_DIR}/includes/headers
    ${glfw_SOURCE_DIR}/include
    ${assimp_SOURCE_DIR}/include 
    ${glm_SOURCE_DIR}
    ${stb_SOURCE_DIR}
  PRIVATE
    ${ZLIB_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  ${PROJECT_SOURCE_DIR}/includes/libassimp.a
  ${PROJECT_SOURCE_DIR}/includes/libglfw3.a
  ${PROJECT_SOURCE_DIR}/includes/libglm.a
  ${PROJECT_SOURCE_DIR}/includes/libJaroViewer.a
)
