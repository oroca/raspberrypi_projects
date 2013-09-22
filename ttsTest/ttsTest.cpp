#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
    char cmd[26];
    char tts[128];
    char say[14];

    strcpy(cmd,"pico2wave --wave say.wav ");
    strcpy(say,"aplay say.wav");

    snprintf(tts, 128, "%s\"%s\"", cmd, "Hello, My friend.");
    system(tts);
    system(say);

    snprintf(tts, 128, "%s\"%s\"", cmd, "My name is ralex.");
    system(tts);
    system(say);

    snprintf(tts, 128, "%s\"%s\"", cmd, "Nice to meet you.");
    system(tts);
    system(say);

    return 0;
}
