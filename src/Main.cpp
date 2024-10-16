#include <Arduino.h>
#include "Global.h"
#include "MelodyMaker.h"


extern Melody *melodyMaker;

extern LcdState lcdState;

// Functieprototypes
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
