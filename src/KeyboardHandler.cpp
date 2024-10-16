#include <Arduino.h>
#include "MelodyMaker.h"
#include "KeyboardHandler.h"

int count = 0;

void handleKeypads()
{
  if (!isAnyKeypad())
    return;
  switch (pressedKeypad)
  {
  case KeypadState::NAVIGATION:
    melodyMaker->loadDemo();
    Serial.println("Navigate");

    break;
  case KeypadState::TIMINGS:
    melodyMaker->addLength(currentKey);
    Serial.println("Timings");
    break;
  case KeypadState::NOTES:
    melodyMaker->addNote(currentKey);
    Serial.println(melodyMaker->getNoteName());
    break;
  case KeypadState::NO_ACTION:
    // Do nothing
    break;
  }
}

void loopKeypads()
{
  char navi, time, note;
  bool keyPressed = false;

  do
  {
    navi = navigationInput.getKey();
    time = timingInput.getKey();
    note = noteInput.getKey();
    keyPressed = navi || time || note; // Set keyPressed to true if any key is detected

  } while (keyPressed && (millis() - lastDebounceTime) < debounceDelay);

  if (keyPressed)
  {

    lastDebounceTime = millis();

    trySetCurrentKeypadState(navi, KeypadState::NAVIGATION);
    trySetCurrentKeypadState(time, KeypadState::TIMINGS);
    trySetCurrentKeypadState(note, KeypadState::NOTES);

    // handleKeys now
    handleKeypads();
  }
  // immediately elliminate the pressedKeypad state
  pressedKeypad = KeypadState::NO_ACTION;
}