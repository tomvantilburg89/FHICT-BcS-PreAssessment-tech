#include <Arduino.h>
#include "MelodyMaker.h"
#include "KeyboardHandler.h"
#include "LcdHelper.h"
#include "MenuState.h"

MenuState currentMenuState = MenuState::MAIN;

extern LcdHelper *lcdHelper;
int count = 0;

void handleNavigation();
void handleKeypads();
void trySetCurrentKeypadState(char key, KeypadState state);

void handleKeypads()
{
  if (!isAnyKeypad())
    return;

  switch (pressedKeypad)
  {
  case KeypadState::NAVIGATION:
    handleNavigation();
    break;
  case KeypadState::TIMINGS:
    if (currentMenuState == MenuState::CREATE)
      melodyMaker->addLength(currentKey);
    break;
  case KeypadState::NOTES:
    if (currentMenuState == MenuState::CREATE)
      melodyMaker->addNote(currentKey);
    break;
  case KeypadState::NO_ACTION:
    // Do nothing
    break;
  }
}

void handleNavigation()
{
  if (!pressedKey && pressedKeypad != KeypadState::NAVIGATION && pressedKeypad != KeypadState::NO_ACTION)
    return;

  switch (pressedKey)
  {
  case '1':
    currentMenuState = MenuState::CREATE;
    break;
  case '4':
    if (currentMenuState != MenuState::CREATE)
      currentMenuState = MenuState::PREVIEW;
    melodyMaker->playDemo();
    break;
  case '6':
    currentMenuState = MenuState::MAIN;
    break;
  case '*':
    break;
  case '#':
    // melodyMaker->stop();
    break;
  }
}

void loopKeypads()
{
  char navi, time, note;
  bool keyPressed = false;
  unsigned long currentDebounceTime = millis();

  do
  {
    navi = navigationInput.getKey();
    time = timingInput.getKey();
    note = noteInput.getKey();
    keyPressed = navi || time || note; // Set keyPressed to true if any key is detected

    if (keyPressed)
    {

      lastDebounceTime = currentDebounceTime;

      trySetCurrentKeypadState(navi, KeypadState::NAVIGATION);
      trySetCurrentKeypadState(time, KeypadState::TIMINGS);
      trySetCurrentKeypadState(note, KeypadState::NOTES);

      // handleKeys now
      handleKeypads();
    }
    // immediately elliminate the pressedKeypad state
    pressedKeypad = KeypadState::NO_ACTION;

  } while (keyPressed && (currentDebounceTime - lastDebounceTime) < debounceDelay);
}