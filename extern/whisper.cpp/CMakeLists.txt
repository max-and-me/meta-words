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
set(MAM_WHISPER_CPP_MODEL_FILE_NAME "ggml-base.en.bin")
set(MAM_WHISPER_CPP_MODEL_OUTPUT_DIR ${PROJECT_BINARY_DIR}/whisper.cpp/models)
if(EXISTS "${MAM_WHISPER_CPP_MODEL_OUTPUT_DIR}/${MAM_WHISPER_CPP_MODEL_FILE_NAME}")
    return()
endif()
message(STATUS "[MAM] Downloading model file ...")
file(DOWNLOAD 
    https://huggingface.co/ggerganov/whisper.cpp/resolve/main/${MAM_WHISPER_CPP_MODEL_FILE_NAME}
    ${MAM_WHISPER_CPP_MODEL_OUTPUT_DIR}/${MAM_WHISPER_CPP_MODEL_FILE_NAME}
    SHOW_PROGRESS
)
