#include "localLLM.h"

LocalLLM::LocalLLM() {
    setPrompt();
}

void LocalLLM::setPrompt() {
    std::ifstream file("llm/prompt.txt");
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            serverPrompt += line + "\n";
        }
        file.close();
    } else {
        throw std::runtime_error("Could not open prompt.txt");
    }
}

std::string LocalLLM::generateResponseString(const std::string& prompt) {
    try {
        ollama::response response = model.generate(modelName,serverPrompt + prompt);
        std::string simple_string = response.as_simple_string();
        //nlohmann::json data = response.as_json();
        return simple_string;
    } catch (ollama::exception& e) {
        std::cout << "Make sure Ollama is set up correctly:  " << e.what() << std::endl;
        throw;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        throw;
    }
}
