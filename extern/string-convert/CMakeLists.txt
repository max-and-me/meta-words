cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(
    string-convert
    GIT_REPOSITORY https://github.com/max-and-me/string-convert.git
    GIT_TAG b3b431763a0bc55ffdceadc190801b6e856788f2
)

FetchContent_MakeAvailable(string-convert)
