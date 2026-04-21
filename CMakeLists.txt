cmake_minimum_required(VERSION 3.20)
project(voiceAssistant)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 1.10.0 # Use the latest release version
)
FetchContent_MakeAvailable(cpr)

find_library(ESPEAK_LIB NAMES espeak-ng)

include_directories(/opt/homebrew/include)

add_executable(voiceAssistant main.cpp
        llm/localLLM.cpp
        llm/localLLM.h)

target_link_libraries(voiceAssistant PRIVATE ${ESPEAK_LIB} cpr::cpr)