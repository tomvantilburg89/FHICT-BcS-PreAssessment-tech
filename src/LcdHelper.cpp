#include <Arduino.h>
#include "LcdHelper.h"

extern Melody *melodyMaker;

int cursorX = 0;
int cursorY = 0;

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
    this->menu.print("1: Create");
    this->menu.setCursor(0, 1);
    this->menu.print("2: -------");
    this->menu.setCursor(0, 2);
    this->menu.print("3: Demo");
}

void LcdHelper::initDemoMenu()
{
    this->clearMenuLCD();
    this->menu.setCursor(0, 0);
    this->menu.print("Playing:");
    this->menu.setCursor(0, 2);
    this->menu.print("Mary had");
    this->menu.setCursor(0, 3);
    this->menu.print("a little lamb");
}
void LcdHelper::initCreateMenuLCD()
{
    this->clearMenuLCD();
    this->clearInfoLCD();
    this->initInfoLCD();
    this->menu.setCursor(0, 0);
    this->menu.print("1: Clear ");
    this->menu.setCursor(0, 1);
    this->menu.print("2: -------");
    this->menu.setCursor(0, 2);
    this->menu.print("3: Main");

    this->updateInfoBpm();
}

void LcdHelper::initSaveMenuLCD()
{
    this->clearMenuLCD();
    this->clearInfoLCD();
    this->menu.setCursor(0, 0);
    this->menu.print("1: Save ");
    this->menu.setCursor(0, 1);
    this->menu.print("2: -------");;
    this->menu.setCursor(0, 2);
    this->menu.print("3: Main");
}
void LcdHelper::initStorageMenu()
{
    this->clearMenuLCD();
    this->clearInfoLCD();
    this->menu.setCursor(0, 0);
    this->menu.print("1: Open ");
    this->menu.setCursor(0, 1);
    this->menu.print("2: -------");
    this->menu.setCursor(0, 2);
    this->menu.print("3: Main");
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
    this->updateInfoBpm();
}

void LcdHelper::updateInfoBpm()
{

    this->info.setCursor(0, 0);
    this->info.print("+/- ");
    if (melodyMaker->getBpm() < 100)
        this->info.print(" ");

    this->info.print(melodyMaker->getBpm());
    this->info.print(" BPM ");
}

void LcdHelper::updateInfoFrequency()
{
    this->info.setCursor(0, 2);

    if (melodyMaker->getNoteFrequency() == 0.0)
    {
        this->info.print("000.00");
    }
    else
    {

        this->info.print(melodyMaker->getNoteFrequency());
    }
    this->info.print(" Hz ");
}

void LcdHelper::updateInfoNoteName()
{
    this->info.setCursor(18, 0);
    this->info.print(melodyMaker->getNoteName());
}

void LcdHelper::updateInfoNoteLength()
{

    this->info.setCursor(0, 3);
    if (melodyMaker->getNoteLength() > 1)
    {
        this->info.print("1/");
    }
    this->info.print(melodyMaker->getNoteLength());
    this->info.print("     ");
}

void LcdHelper::updateInfoLCD()
{
    this->updateInfoBpm();
    this->updateInfoNoteName();
    this->updateInfoNoteLength();
    this->updateInfoFrequency();
}

void LcdHelper::clearMelodyLCD()
{
    cursorX = 0;
    cursorY = 0;

    this->melody.clear();
    this->melody.setCursor(0, 0);
}

void LcdHelper::updateMelodyLCD()
{
    this->melody.setCursor(cursorX, cursorY);
    const char *name = melodyMaker->getNoteName();

    this->melody.print(name);
    int len = String(name).length();

    cursorX += len;

    if (cursorX >= 19 && cursorY < 4)
    {
        cursorX = 0;
        cursorY++;
        if (cursorY == 4)
        {
            cursorY = 0;
            this->melody.clear();
        }
    }
}
