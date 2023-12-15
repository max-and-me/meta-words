cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(
    fast-cpp-csv-parser
    GIT_REPOSITORY https://github.com/ben-strasser/fast-cpp-csv-parser.git
    GIT_TAG 4ade42d5f8c454c6c57b3dce9c51c6dd02182a66
)

FetchContent_MakeAvailable(fast-cpp-csv-parser)

add_library(fast-cpp-csv-parser INTERFACE)

target_include_directories(fast-cpp-csv-parser
    INTERFACE 
        ${fast-cpp-csv-parser_SOURCE_DIR}
)