#ifndef LCD_HELPER_H
#define LCD_HELPER_H

#include <Wire.h>
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "Global.h"

class LcdHelper
{
public:
    LcdHelper();
    LcdState selected;
    uint8_t *addresses;
    Melody melodyMaker;

    void setup();
    void init();
    void updateMelodyLCD();

private:
    LiquidCrystal_I2C *lcds;
    LiquidCrystal_I2C lcd(LcdState state);
    LiquidCrystal_I2C menu();
    LiquidCrystal_I2C info();
    LiquidCrystal_I2C melody();
};

#endif
