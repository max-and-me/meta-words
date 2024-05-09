cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(
    whisper.cpp
    GIT_REPOSITORY https://github.com/ggerganov/whisper.cpp.git
    GIT_TAG v1.5.5
)

option(WHISPER_BUILD_EXAMPLES "whisper: build examples" ON)

FetchContent_MakeAvailable(whisper.cpp)

# Cache the models download directory
set(MAM_WHISPER_CPP_MODEL_DOWNLOAD_DIR "${PROJECT_BINARY_DIR}/whisper.cpp/models" CACHE PATH "MAM whisper.cpp models models diretory")

# Only download if not exist already
set(MAM_WHISPER_CPP_MODEL_FILE_NAME "ggml-base.en.bin")
if(EXISTS "${MAM_WHISPER_CPP_MODEL_DOWNLOAD_DIR}/${MAM_WHISPER_CPP_MODEL_FILE_NAME}")
    return()
endif()
message(STATUS "[MAM] Downloading model file ...")
file(DOWNLOAD 
    https://huggingface.co/ggerganov/whisper.cpp/resolve/main/${MAM_WHISPER_CPP_MODEL_FILE_NAME}
    ${MAM_WHISPER_CPP_MODEL_DOWNLOAD_DIR}/${MAM_WHISPER_CPP_MODEL_FILE_NAME}
    SHOW_PROGRESS
)
