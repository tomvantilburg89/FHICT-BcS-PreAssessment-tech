/**
 * #######################################################################################################################################
 *
 *  Keyboard | Fields, Properties | TODO: Needs encapsulation
 *
 * ####################################################################################################################################### */

#ifndef KEYPADS_H
#define KEYPADS_H

#include <Keypad.h>
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Global.h"

const byte ROWS = 4; // vier rijen
const byte COLS = 4; // vier kolommen

const char keys_4x3[ROWS][COLS - 1] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};


byte navigationRowPins[ROWS] = {9, 8, 7, 6}; // verbind met de rij pinouts van het keypad
byte navigationColPins[COLS] = {5, 4, 3, 2}; // verbind met de kolom pinouts van het keypad

byte noteRowPins[ROWS] = {A7, A6, A5, A4}; // verbind met de rij pinouts van het keypad
byte noteColPins[COLS] = {A3, A2, A1};     // verbind met de kolom pinouts van het keypad

byte timingRowPins[ROWS] = {A15, A14, A13, A12}; // verbind met de rij pinouts van het keypad
byte timingColPins[COLS] = {A11, A10, A9};       // verbind met de kolom pinouts van het keypad

Keypad navigationInput = Keypad(makeKeymap(keys_4x3), navigationRowPins, navigationColPins, ROWS, COLS - 1);
Keypad noteInput = Keypad(makeKeymap(keys_4x3), noteRowPins, noteColPins, ROWS, COLS - 1);
Keypad timingInput = Keypad(makeKeymap(keys_4x3), timingRowPins, timingColPins, ROWS, COLS - 1);

extern const char *namedNotesMap[];
extern Melody *melodyMaker;
extern KeypadState pressedKeypad;

/**
 * #######################################################################################################################################
 *
 *  Keyboard | Fields, Properties
 *
 * ####################################################################################################################################### */

char currentKey;
int currentKeyIndex;
bool isPlaying = false;

// Debounce keypresses
const unsigned long debounceDelay = 50;
unsigned long lastDebounceTime = 0;

void trySetCurrentKeypadState(char key, KeypadState state)
{
    if (!key)
        return;

    currentKey = melodyMaker->getKeyPress(key);
    pressedKeypad = state;
}

bool isKeypad(KeypadState state)
{
    return pressedKeypad == state;
}

bool isAnyKeypad()
{
    return pressedKeypad < KeypadState::NO_ACTION;
}

#endif