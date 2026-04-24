//
// Created by Tim Healey on 4/23/26.
//
#include <string>
#include <iostream>
#include "llm/localLLM.h"
#include "nlohmann/json.hpp"
#include <cpr/cpr.h>

#ifndef VOICEASSISTANT_API_H
#define VOICEASSISTANT_API_H


class API {
public:
    static std::string callExternalLLM(const std::string& prompt);
};


#endif //VOICEASSISTANT_API_H