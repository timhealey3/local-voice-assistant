#include <iostream>
#include <string>
#include "llm/localLLM.h"
#include "nlohmann/json.hpp"
#include "API.h"
#include "audio/audioUtil.h"

enum class OutputEnum { spotify, light, unsure };

OutputEnum convertResponseEnum(const std::string& response) {
    std::unordered_map<std::string, OutputEnum> map = {
        {"spotify", OutputEnum::spotify},
        {"light", OutputEnum::light},
        {"unsure", OutputEnum::unsure}
    };
    auto it = map.find(response);
    return it != map.end() ? it->second : OutputEnum::unsure;
}

std::string decisionRouter(const OutputEnum& outputEnum, const nlohmann::json& jsonResponse) {
    std::string res;
    switch (outputEnum) {
        case OutputEnum::spotify:
            std::cout << "spotify" << std::endl;
            break;
        case OutputEnum::light:
            std::cout << "light" << std::endl;
            break;
        case OutputEnum::unsure:
            std::cout << "unsure" << std::endl;
            auto TODO = "TODO IMPLEMENT THIS";
            res = API::callExternalLLM(TODO);
            break;
    }
    return res;
}

int main() {
    // arduino board to capture input
    // take in text
    constexpr std::string inputText = "This is a test text";
    LocalLLM localLLM;
    std::string response = localLLM.generateResponseString(inputText);
    nlohmann::json jsonResponse = nlohmann::json::parse(response);
    std::cout << jsonResponse << std::endl;

    OutputEnum outputEnum = convertResponseEnum(jsonResponse["toolName"]);
    std::string decisionResponse = decisionRouter(outputEnum, jsonResponse);
    audioUtil::playAudio(decisionResponse);
    return 0;
}