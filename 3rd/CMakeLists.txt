include(FetchContent)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog
    GIT_TAG         v1.12.0
)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2
    GIT_TAG         v3.4.0
)

FetchContent_MakeAvailable(spdlog)
FetchContent_MakeAvailable(Catch2)
