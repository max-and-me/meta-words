cmake_minimum_required(VERSION 3.19.0)

project("Meta Words")

add_subdirectory(extern)

# library
add_library(meta_words STATIC
    include/mam/meta_words/runner.h
    source/whisper/runner.cpp
)

target_link_libraries(meta_words
    PRIVATE
        tiny-process-library
        fast-cpp-csv-parser
)

target_include_directories(meta_words
    PUBLIC
        include
    PRIVATE
        source
)

target_compile_features(meta_words 
    PRIVATE 
        cxx_std_17
)

# executable
add_executable(meta_words-app
    source/main.cpp
)

target_link_libraries(meta_words-app
    PRIVATE
        meta_words
)

target_compile_features(meta_words-app
    PRIVATE 
        cxx_std_17
)

set_property(
    TARGET
        tiny-process-library
    PROPERTY
        POSITION_INDEPENDENT_CODE ON
)