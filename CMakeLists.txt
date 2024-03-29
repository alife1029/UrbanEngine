cmake_minimum_required(VERSION 3.16)

# Using for supress warning
project(ToSupress)

# C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DURBAN_IS_DEBUG=true")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -DURBAN_IS_DEBUG=false")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUNICODE -D_UNICODE")

if (WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DURBAN_PLATFORM_WINDOWS")
endif()

# Constants and variables
set(URBAN_DIR ${CMAKE_SOURCE_DIR}/UrbanEngine)
set(URBAN_INCLUDES)
set(URBAN_LINKS)
set(TEST_APP_DIR ${CMAKE_SOURCE_DIR}/TestApp)
set(TEST_APP_INCLUDES)
set(TEST_APP_LINKS)

# Libraries
include(${CMAKE_SOURCE_DIR}/CMake/glad.cmake)
include(${CMAKE_SOURCE_DIR}/CMake/stb.cmake)

# Project CMake Lists
include(${CMAKE_SOURCE_DIR}/CMake/UrbanEngine.cmake)
include(${CMAKE_SOURCE_DIR}/CMake/TestApp.cmake)
