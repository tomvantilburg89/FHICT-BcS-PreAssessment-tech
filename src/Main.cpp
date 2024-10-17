#include <Arduino.h>
#include "Global.h"
#include "MelodyMaker.h"
#include "LcdHelper.h"
#include "MenuState.h"

extern Melody *melodyMaker;
extern LcdHelper *lcdHelper;
extern LcdState lcdState;

// Functieprototypes
void loopKeypads();

// program
void setup()
{
  Serial.begin(9600);

  melodyMaker = new Melody(160);
  lcdHelper = new LcdHelper();
  lcdHelper->initMenuLCD();
}

void loop()
{
  loopKeypads();
  melodyMaker->play();
}
