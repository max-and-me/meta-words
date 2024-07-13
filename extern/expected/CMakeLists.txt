cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(
    std-expected
    GIT_REPOSITORY https://github.com/TartanLlama/expected.git
    GIT_TAG v1.1.0
)

FetchContent_MakeAvailable(std-expected)
