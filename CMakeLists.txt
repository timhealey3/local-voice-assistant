cmake_minimum_required(VERSION 3.20)
project(voiceAssistant)
set(CMAKE_CXX_STANDARD 20)

find_library(ESPEAK_LIB NAMES espeak-ng)

include_directories(/opt/homebrew/include)

add_executable(voiceAssistant main.cpp
        llm/localLLM.cpp
        llm/localLLM.h)

target_link_libraries(voiceAssistant PRIVATE ${ESPEAK_LIB})