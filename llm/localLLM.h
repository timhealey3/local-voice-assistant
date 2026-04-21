#include "ollama.hpp"
#include <string>

#ifndef VOICEASSISTANT_LOCALLLM_H
#define VOICEASSISTANT_LOCALLLM_H


class LocalLLM {
public:
    LocalLLM();
    void setPrompt();
    std::string generateResponseString(const std::string& prompt);
private:
    Ollama model;
    std::string modelName = "qwen3:0.6b";
    std::string serverPrompt;
};


#endif //VOICEASSISTANT_LOCALLLM_H