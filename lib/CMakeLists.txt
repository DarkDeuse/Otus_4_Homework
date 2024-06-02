cmake_minimum_required(VERSION 3.2)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(version VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(version VERSION 0.0.1)
endif()

configure_file(version_def.h.in ${PROJECT_SOURCE_DIR}/version_def.h)

add_library(${PROJECT_NAME} version.cpp version.h version_def.h)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic")
endif()
