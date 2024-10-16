#include "LcdHelper.h"

LiquidCrystal_I2C menuLCD(0x27, 20, 4);
LiquidCrystal_I2C infoLCD(0x28, 20, 4);
LiquidCrystal_I2C melodyLCD(0x29, 20, 4);

extern LcdState lcdState;
extern Melody *melodyMaker;

LcdHelper::LcdHelper()
{
}

void LcdHelper::setup()
{
    menuLCD.init();
    menuLCD.backlight();
    infoLCD.init();
    infoLCD.backlight();
    melodyLCD.init();
    melodyLCD.backlight();
}

LiquidCrystal_I2C LcdHelper::menu()
{
    return menuLCD;
}

LiquidCrystal_I2C LcdHelper::info()
{
    return infoLCD;
}

LiquidCrystal_I2C LcdHelper::melody()
{
    return melodyLCD;
}

void LcdHelper::updateMelodyLCD()
{
    this->melody().print(melodyMaker->getNoteName());
}