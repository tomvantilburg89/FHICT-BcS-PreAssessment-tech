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
    
    void init();

    void initMenuLCD();
    void initInfoLCD();

    void updateInfoLCD();
    
    void updateInfoBpm();
    void updateInfoFrequency();
    void updateInfoNoteName();
    void updateInfoNoteLength();

    void updateMelodyLCD();

    void clearMenuLCD();
    void clearInfoLCD();
    void clearMelodyLCD();

private:
    Melody *music;
    LiquidCrystal_I2C menu = LiquidCrystal_I2C(0x27, 20, 4);
    LiquidCrystal_I2C info = LiquidCrystal_I2C(0x28, 20, 4);
    LiquidCrystal_I2C melody = LiquidCrystal_I2C(0x29, 20, 4);
};

#endif
