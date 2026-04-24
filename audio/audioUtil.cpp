//
// Created by Tim Healey on 4/23/26.
//
#include "audioUtil.h"

void audioUtil::playAudio(const std::string& text) {
    try {
        espeak_Initialize(AUDIO_OUTPUT_PLAYBACK, 0, NULL, 0);
        espeak_Synth(text.c_str(), text.length() + 1, 0, POS_CHARACTER, 0, espeakCHARS_AUTO, NULL, NULL);
        espeak_Synchronize();
    } catch (std::exception& e) {
        std::cerr << "Audio failed to play: "  << e.what() << std::endl;
    }
}
