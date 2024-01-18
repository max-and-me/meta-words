cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(
    utf-8-everywhere
    GIT_REPOSITORY https://github.com/max-and-me/utf-8-everywhere.git
    GIT_TAG a8990824a724fe9dc1284f2c9305d00f5c84ff72
)

FetchContent_MakeAvailable(utf-8-everywhere)
