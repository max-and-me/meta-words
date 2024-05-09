cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(
    utf-8-everywhere
    GIT_REPOSITORY https://github.com/max-and-me/utf-8-everywhere.git
    GIT_TAG b9dd0d89f49446d02d1a3a242aef484d625418db
)

FetchContent_MakeAvailable(utf-8-everywhere)
