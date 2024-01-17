cmake_minimum_required(VERSION 3.19.0)

project("Meta Words")

add_subdirectory(extern)

# library
add_library(meta-words STATIC
    include/mam/meta_words/runner.h
    source/whisper.cpp/runner.cpp
)

target_link_libraries(meta-words
    PRIVATE
        tiny-process-library
        fast-cpp-csv-parser
)

if(MSVC)
    target_compile_definitions (tiny-process-library 
        PUBLIC 
            -D_UNICODE -DUNICODE
    )
endif()

if(WIN32)
    target_link_libraries(meta-words
        PRIVATE
            utf-8-everywhere
    )
endif()

target_include_directories(meta-words
    PUBLIC
        include
    PRIVATE
        source
)

target_compile_features(meta-words
    PRIVATE 
        cxx_std_17
)

# executable
add_executable(meta-words-app
    source/main.cpp
)

target_link_libraries(meta-words-app
    PRIVATE
        meta-words
)

target_compile_features(meta-words-app
    PRIVATE 
        cxx_std_17
)

set_property(
    TARGET
        tiny-process-library
    PROPERTY
        POSITION_INDEPENDENT_CODE ON
)