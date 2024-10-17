/**
 * #######################################################################################################################################
 *
 *  Global.h - holds most of the initial configuration state for the entire projects
 *
 * ####################################################################################################################################### */

#ifndef GLOBALS_H
#define GLOBALS_H

#include "MelodyMaker.h"
#include <LiquidCrystal_I2C.h>

extern uint8_t i2cAddresses[];

enum KeypadState
{
    NAVIGATION,
    TIMINGS,
    NOTES,
    NO_ACTION,
};

enum LcdState
{
    MENU,
    INFO,
    MELODY,
    NO_LCD
};


extern const int BUZZER_PIN;
extern const float BASE_FREQUENCY;
extern const char *namedNotesMap[];

extern char currentKey;
extern const char *namedNotesMap[];

extern KeypadState pressedKeypad;

extern int getKeyIndex(char key);
extern bool isAnyKeypad();
extern bool isKeypad(KeypadState state);

extern const int demoFreq[];
extern const int demoLen[];


#endif