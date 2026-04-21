#include <iostream>
#include <string>
#include <espeak-ng/speak_lib.h>
#include "llm/localLLM.h"
#include "nlohmann/json.hpp"
#include "crow.h"

enum class OutputEnum { spotify, light, unsure };

void callLargeModel() {
    // post request to large model
}

OutputEnum convertResponseEnum(std::string response) {
    std::unordered_map<std::string, OutputEnum> map = {
        {"spotify", OutputEnum::spotify},
        {"light", OutputEnum::light},
        {"unsure", OutputEnum::unsure}
    };
    auto it = map.find(response);
    return it != map.end() ? it->second : OutputEnum::unsure;
}

void decisionRouter(OutputEnum outputEnum) {
    switch (outputEnum) {
        case OutputEnum::spotify:
            std::cout << "spotify" << std::endl;

            break;
        case OutputEnum::light:
            std::cout << "light" << std::endl;
            break;
        case OutputEnum::unsure:
            std::cout << "unsure" << std::endl;
            callLargeModel();
            break;
    }
}

void playAudioResponse(std::string text) {
    espeak_Initialize(AUDIO_OUTPUT_PLAYBACK, 0, NULL, 0);
    espeak_Synth(text.c_str(), text.length() + 1, 0, POS_CHARACTER, 0, espeakCHARS_AUTO, NULL, NULL);
    espeak_Synchronize();
}

int main() {
    // arduino board to capture input
    // take in text
    constexpr std::string inputText = "This is a test text";
    LocalLLM localLLM;
    std::string response = localLLM.generateResponseString(inputText);
    nlohmann::json response2 = nlohmann::json::parse(response);
    std::cout << response2 << std::endl;

    OutputEnum outputEnum = convertResponseEnum(response2["toolName"]);
    decisionRouter(outputEnum);
    // output LLM
    playAudioResponse(response2["unsureData"]["textOutput"]);
    return 0;
}