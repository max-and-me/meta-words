cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(
    whisper.cpp
    GIT_REPOSITORY https://github.com/ggerganov/whisper.cpp.git
    GIT_TAG f6614155e40198bad739fed9400d0de8de9cc311
)

option(WHISPER_BUILD_EXAMPLES "whisper: build examples" ON)

FetchContent_MakeAvailable(whisper.cpp)

# Only download if not exist already
if(EXISTS "${PROJECT_BINARY_DIR}/whipser.cpp/ggml-base.en.bin")
    return()
endif()
message(STATUS "[MAM] Downloading model file ...")
file(DOWNLOAD 
    https://huggingface.co/ggerganov/whisper.cpp/resolve/main/ggml-base.en.bin
    ${PROJECT_BINARY_DIR}/whipser.cpp/ggml-base.en.bin
    SHOW_PROGRESS
)
