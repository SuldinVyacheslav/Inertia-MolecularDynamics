cmake_minimum_required(VERSION 3.1)

project(ProjectName)

set(This Tests)

set(Sources
    Test.cpp
)

add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
    gtest_main
)

add_test(
    NAME ${This}
    COMMAND ${This}
)