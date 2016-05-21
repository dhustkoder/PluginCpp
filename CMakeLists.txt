cmake_minimum_required(VERSION 2.6)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
project(XChip)


set(MEMORY_SANITIZER "OFF" CACHE STRING "-fsanitize=memory")
set(UNDEFINED_SANITIZER "OFF" CACHE STRING "-fsanitize=undefined")

# compiler settings flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11 -pedantic")

if( ${MEMORY_SANITIZER} STREQUAL "ON" )
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=memory")
elseif( ${UNDEFINED_SANITIZER} STREQUAL "ON" )
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined") 
endif()

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${PROJECT_INCLUDE_DIR} /usr/local/include) 
link_directories(/usr/local/lib)


add_subdirectory(${PROJECT_SOURCE_DIR})
