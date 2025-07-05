cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(
    fast-cpp-csv-parser
    GIT_REPOSITORY https://github.com/ben-strasser/fast-cpp-csv-parser.git
    GIT_TAG 574a9fe4d323ba63416877a4a5fe59088d37aa34
)

FetchContent_MakeAvailable(fast-cpp-csv-parser)

add_library(fast-cpp-csv-parser INTERFACE)

target_include_directories(fast-cpp-csv-parser
    INTERFACE 
        ${fast-cpp-csv-parser_SOURCE_DIR}
)
