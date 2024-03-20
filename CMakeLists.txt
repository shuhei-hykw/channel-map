# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
cmake_host_system_information(RESULT host QUERY HOSTNAME)
if(host MATCHES ".kek\.jp")
  message(STATUS "The hostname is ${host}")
  set(CMAKE_C_COMPILER /opt/gcc-8.3.0/bin/gcc)
  set(CMAKE_CXX_COMPILER /opt/gcc-8.3.0/bin/g++)
endif()
project(DetectorMapping VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_BUILD_RPATH ${CMAKE_INSTALL_PREFIX}/lib)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

### main library
add_library(DetectorMapping SHARED ${SOURCES})
target_include_directories(DetectorMapping PUBLIC include
					   external/yaml-cpp/include
					   external/jsoncpp/include)
target_include_directories(DetectorMapping PRIVATE
					    external/yaml-cpp/include
					    external/jsoncpp/include)
target_link_libraries(DetectorMapping PRIVATE yaml-cpp)
target_link_libraries(DetectorMapping PRIVATE jsoncpp_lib)

add_subdirectory(external/yaml-cpp)
add_subdirectory(external/jsoncpp)

### for test
add_executable(test_program test.cpp)
target_link_libraries(test_program PRIVATE yaml-cpp jsoncpp_lib
				   DetectorMapping)

### install
install(TARGETS test_program DESTINATION bin)
install(TARGETS DetectorMapping DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)
