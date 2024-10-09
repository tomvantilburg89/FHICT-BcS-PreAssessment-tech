#include <Arduino.h>
#include "Global.h"
#include "MelodyMaker.h"
#include "LcdHelper.h"

extern Melody *melodyMaker;
extern LcdHelper lcdHelper;
extern LcdState lcdState;

// Functieprototypes
void setupLCDs();
void loopKeypads();

// handlers
void handleKeypads();


// program
void setup()
{
  melodyMaker = new Melody(180);
  Serial.begin(9600);
}

void loop()
{
  loopKeypads();
}
