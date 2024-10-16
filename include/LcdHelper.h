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
    void setup();
    void updateMelodyLCD();

    LiquidCrystal_I2C menu();
    LiquidCrystal_I2C info();
    LiquidCrystal_I2C melody();

private:
};

#endif
