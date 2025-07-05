cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(
    expected-lite
    GIT_REPOSITORY https://github.com/martinmoene/expected-lite.git
    GIT_TAG v0.9.0
)

FetchContent_MakeAvailable(expected-lite)
