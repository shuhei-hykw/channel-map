# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(DetectorMapping VERSION 0.1)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

add_library(DetectorMapping SHARED ${SOURCES})
target_include_directories(DetectorMapping PUBLIC include)

# for test
add_executable(test_program test.cpp)
target_link_libraries(test_program PRIVATE DetectorMapping)

# cleanup tool
add_custom_target(clean_target
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/lib
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/CMakeFiles
  COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/Makefile
)

install(TARGETS DetectorMapping DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)
