cmake_minimum_required(VERSION 3.2)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(tests VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(tests VERSION 0.0.1)
endif()

include(GoogleTest)

add_executable(${PROJECT_NAME} test.cpp)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic")
endif()

target_link_libraries(
  ${PROJECT_NAME}
  ${GTEST_BOTH_LIBRARIES}
  pthread
  version
)

add_test(tests ${PROJECT_NAME})

enable_testing()
