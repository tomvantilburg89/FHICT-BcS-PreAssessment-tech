#include <Arduino.h>
#include "LcdHelper.h"

extern Melody *melodyMaker;

LcdHelper::LcdHelper()
{
    this->init();
}

void LcdHelper::init()
{
    menu.init();
    info.init();
    melody.init();
    menu.backlight();
    info.backlight();
    melody.backlight();
};

void LcdHelper::initMenuLCD()
{
    this->menu.setCursor(0, 0);
    this->menu.print("1 ) Create melody");
    this->menu.setCursor(0, 1);
    this->menu.print("2 ) Stored melodies");
    this->menu.setCursor(0, 2);
    this->menu.print("3 ) Play default");
    this->updateInfoBpm();
}

void LcdHelper::clearMenuLCD()
{
    this->menu.clear();
}

void LcdHelper::clearInfoLCD()
{
    this->info.clear();
}

void LcdHelper::initInfoLCD()
{
    this->info.setCursor(0, 0);
    this->info.print("BPM: ");
    this->info.print(melodyMaker->getBpm());
    this->info.setCursor(0, 1);
    this->info.print("Frequency: ");
    this->info.print(" ");
    this->info.setCursor(0, 2);
    this->info.print("Note: ");
    this->info.print(" ");
    this->info.print(" ");
    this->info.setCursor(0, 3);
    this->info.print("Timing: ");
    this->info.print(" ");
    this->info.print(" ");
}

void LcdHelper::updateInfoBpm()
{

    this->info.setCursor(0, 0);
    this->info.print("BPM: ");
    this->info.print(melodyMaker->getBpm());
    this->info.print(" ");
}

void LcdHelper::updateInfoFrequency()
{
    this->info.setCursor(0, 1);
    this->info.print("Frequency: ");
    this->info.print(melodyMaker->getNoteFrequency());
}

void LcdHelper::updateInfoNoteName()
{
    this->info.setCursor(0, 2);
    this->info.print("Note: ");
    this->info.print(melodyMaker->getNoteName());
    this->info.print(" ");
}
void LcdHelper::updateInfoNoteLength()
{
    this->info.setCursor(0, 3);
    this->info.print("Timing: ");
    this->info.print(melodyMaker->getNoteLength());
    this->info.print(" ");
}

void LcdHelper::updateInfoLCD()
{
    this->updateInfoBpm();
    this->updateInfoFrequency();
    this->updateInfoNoteName();
    this->updateInfoNoteLength();
}

void LcdHelper::clearMelodyLCD()
{
    this->melody.clear();
}

void LcdHelper::updateMelodyLCD()
{
    this->melody.print(melodyMaker->getNoteName());
}