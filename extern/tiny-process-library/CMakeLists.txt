cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(
    tiny-process-library
    GIT_REPOSITORY https://gitlab.com/eidheim/tiny-process-library.git
    GIT_TAG 8bbb5a211c5c9df8ee69301da9d22fb977b27dc1
)

option(BUILD_TESTING "" OFF)

FetchContent_MakeAvailable(tiny-process-library)
