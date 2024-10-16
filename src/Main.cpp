#include <Arduino.h>
#include "Global.h"
#include "MelodyMaker.h"
#include "LcdHelper.h"

extern Melody *melodyMaker;
extern LcdHelper *lcdHelper;
extern LcdState lcdState;

// Functieprototypes
void loopKeypads();

// program
void setup()
{
  Serial.begin(9600);

  melodyMaker = new Melody(180);
  lcdHelper = new LcdHelper();
  lcdHelper->initMenuLCD();
}

void loop()
{
  loopKeypads();
}
