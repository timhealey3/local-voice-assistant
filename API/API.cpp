//
// Created by Tim Healey on 4/23/26.
//

#include "API.h"

std::string API::callExternalLLM(const std::string& prompt) {

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
