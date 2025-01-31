cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(
    tiny-process-library
    GIT_REPOSITORY https://gitlab.com/eidheim/tiny-process-library.git
    GIT_TAG v2.0.4
)

option(BUILD_TESTING "" OFF)

FetchContent_MakeAvailable(tiny-process-library)
