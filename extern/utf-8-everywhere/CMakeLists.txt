cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(
    utf-8-everywhere
    GIT_REPOSITORY https://github.com/max-and-me/utf-8-everywhere.git
    GIT_TAG 51e8e1368d9c10d3700ef3d292e94bf85a994af0
)

FetchContent_MakeAvailable(utf-8-everywhere)
