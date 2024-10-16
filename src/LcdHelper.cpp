#include "LcdHelper.h"

extern LcdState lcdState;
extern Melody *melodyMaker;

LcdHelper::LcdHelper() : addresses(i2cAddresses), melodyMaker(melodyMaker)
{
}

void LcdHelper::setup()
{
    for (int i = 0; i < 3; i++)
    {
        this->selected = i;
        this->init(i);
    }
}

void LcdHelper::init(int i)
{
    this->lcd(i).init();
    this->lcd(i).backlight();
}

LiquidCrystal_I2C LcdHelper::lcd(int state)
{
    return LiquidCrystal_I2C(this->addresses[state], 20, 4);
};

LiquidCrystal_I2C LcdHelper::menu()
{
    return this->lcd(LcdState::MENU);
}

LiquidCrystal_I2C LcdHelper::info()
{
    return this->lcd(LcdState::INFO);
}

LiquidCrystal_I2C LcdHelper::melody()
{
    return this->lcd(LcdState::MELODY);
}

void LcdHelper::updateMelodyLCD()
{
    this->melodyMaker->getNoteName();

    Serial.println(this->melodyMaker->getNoteName());
    const char *notename = this->melodyMaker->getNoteName();

    this->melody().print(notename);
}