cmake_minimum_required(VERSION 3.10)

# Project name and version
project(httpserver VERSION 1.0 LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Specify the include directories
include_directories(${PROJECT_SOURCE_DIR}/inc)

# Find Boost libraries
find_package(Boost REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Boost libraries not found!")
endif()

# Add the executable
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(httpserver ${SOURCES})

# Link Boost libraries
target_link_libraries(httpserver ${Boost_LIBRARIES} pthread rt boost_system boost_thread boost_chrono)

