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
    uint8_t *addresses;
    Melody *melodyMaker;

    void setup();
    void init(int i);
    void updateMelodyLCD();

private:
    int selected;
    LiquidCrystal_I2C *lcds;
    LiquidCrystal_I2C lcd(int state);
    LiquidCrystal_I2C menu();
    LiquidCrystal_I2C info();
    LiquidCrystal_I2C melody();
};

#endif
