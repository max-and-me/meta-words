cmake_minimum_required(VERSION 3.19.0)

# Add your dependencies here, e.g. googletest
# add_subdirectory(googletest)

add_subdirectory(tiny-process-library)
add_subdirectory(fast-cpp-csv-parser)
add_subdirectory(whisper.cpp)
if(WIN32)
    add_subdirectory(utf-8-everywhere)
endif()