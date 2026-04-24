//
// Created by Tim Healey on 4/23/26.
//
#include <espeak-ng/speak_lib.h>
#include <string>
#include <iostream>

#ifndef VOICEASSISTANT_AUDIOUTIL_H
#define VOICEASSISTANT_AUDIOUTIL_H


class audioUtil {
public:
    static void playAudio(const std::string& text);
};


#endif //VOICEASSISTANT_AUDIOUTIL_H