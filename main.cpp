#include <iostream>
#include <string>
#include <espeak-ng/speak_lib.h>
#include "llm/localLLM.h"
#include "nlohmann/json.hpp"
#include <cpr/cpr.h>

enum class OutputEnum { spotify, light, unsure };

std::string callLargeModel() {
    std::string prompt = "Explain quantum physics to a cat.";

    cpr::Response r = cpr::Post(
        cpr::Url{"http://localhost:18080/largeLLMCall"},
        cpr::Body{prompt},
        cpr::Header{{"Content-Type", "text/plain"}}
    );

    if (r.status_code == 200) {
        std::cout << "LLM Response: " << r.text << std::endl;
    } else {
        std::cerr << "Error: " << r.status_code << " - " << r.error.message << std::endl;
        throw std::runtime_error(r.error.message);
    }
    return r.text;
}

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
            res = callLargeModel();
            break;
    }
    return res;
}

void playAudioResponse(std::string text) {
    try {
        espeak_Initialize(AUDIO_OUTPUT_PLAYBACK, 0, NULL, 0);
        espeak_Synth(text.c_str(), text.length() + 1, 0, POS_CHARACTER, 0, espeakCHARS_AUTO, NULL, NULL);
        espeak_Synchronize();
    } catch (std::exception& e) {
        std::cerr << "Audio failed to play: "  << e.what() << std::endl;
    }
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
    playAudioResponse(decisionResponse);
    return 0;
}