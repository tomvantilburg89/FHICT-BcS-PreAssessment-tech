#include "Global.h"
#include "MelodyMaker.h"
#include "LcdHelper.h"

Melody *melodyMaker;
KeypadState pressedKeypad;
LcdState lcdState;
LcdHelper lcdHelper;

uint8_t i2cAddresses[] = {0x27, 0x28, 0x29};

const char *namedNotesMap[] = {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};

// Default demo song
const int demoFreq[] = {
    7, 5, 3, 5, 7, 7, 7, 0,   // E D C D E E E *
    5, 5, 5, 0, 7, 10, 10, 0, // D D D * E G G *
    7, 5, 3, 5, 7, 7, 7, 0,   // E D C D E E E *
    7, 5, 5, 7, 5, 3          // E D D E D C
};

const int demoLen[] = {
    2, 4, 2, 4, 2, 4, 2, 4,
    2, 4, 2, 4, 2, 4, 2, 4,
    2, 4, 2, 4, 2, 4, 4, 4,
    4, 2, 4, 2, 4, 1};

const int BUZZER_PIN = 13;
const float BASE_FREQUENCY = 440.0;
const unsigned int MAX_MELODY_LENGTH = 128;