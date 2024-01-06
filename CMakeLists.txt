cmake_minimum_required(VERSION 3.27)
project(naive_bayes_algorithm)

set(CMAKE_CXX_STANDARD 23)

find_package(Boost COMPONENTS REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(naive_bayes_algorithm
        json.hpp
        main.cpp)
target_link_libraries(naive_bayes_algorithm ${Boost_LIBRARIES})
