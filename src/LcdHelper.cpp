#include "LcdHelper.h"

extern LcdState lcdState;
extern Melody *melodyMaker;

LcdHelper::LcdHelper() : selected(lcdState), addresses(i2cAddresses), melodyMaker(melodyMaker)
{
}

void LcdHelper::setup()
{
    for (int i = 0; i < LcdState::NO_LCD; i++)
    {
        this->selected = (LcdState)i;
        this->init();
    }
}

void LcdHelper::init()
{
    this->lcds[this->selected] = this->lcd(this->selected);
    this->lcds[this->selected].init();
    this->lcds[this->selected].backlight();
}

LiquidCrystal_I2C LcdHelper::lcd(LcdState state)
{
    return this->lcds[state] = LiquidCrystal_I2C(this->addresses[state], 20, 4);
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
    const char *notename = melodyMaker.getNoteName();

    this->melody().print(notename);
}