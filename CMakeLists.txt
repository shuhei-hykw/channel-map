# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(DetectorMapping VERSION 0.1)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

add_library(DetectorMapping SHARED ${SOURCES})
target_include_directories(DetectorMapping PUBLIC include)

### yaml-cpp
add_subdirectory(yaml-cpp)

### for test
add_executable(test_program test.cpp)
target_link_libraries(test_program PRIVATE yaml-cpp DetectorMapping)

### install
set(CMAKE_INSTALL_PREFIX .)
install(TARGETS test_program DESTINATION bin)
install(TARGETS DetectorMapping DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)
