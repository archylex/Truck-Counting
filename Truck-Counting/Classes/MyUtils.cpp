//
// Created by alec on 01.11.19.
//

#include "MyUtils.h"


char* MyUtils::intToAudioName(int a) {
    const char* audio_name = to_string(a).c_str();
    const char* atype = ".mp3";
    char * fname = new char[strlen(audio_name) + strlen(atype) + 1];
    strcpy(fname, audio_name);
    strcat(fname, atype);
    return  fname;
}


