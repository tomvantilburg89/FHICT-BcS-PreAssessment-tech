#include <Arduino.h>
#include "MelodyMaker.h"
#include "KeyboardHandler.h"
#include "LcdHelper.h"
#include "MenuState.h"

MenuState currentMenuState = MenuState::MAIN;

extern LcdHelper *lcdHelper;
int count = 0;

void mainMenu();
void handleKeypads();
void handleMainNavigation();
void handleCreateNavigation();
void trySetCurrentKeypadState(char key, KeypadState state);

void handleKeypads()
{
  if (!isAnyKeypad())
    return;

  switch (pressedKeypad)
  {
  case KeypadState::NAVIGATION:
    if (currentMenuState == MenuState::MAIN)
      handleMainNavigation();
    if (currentMenuState == MenuState::CREATE)
      handleCreateNavigation();
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

void handleMainNavigation()
{
  if (!pressedKey && pressedKeypad != KeypadState::NAVIGATION && pressedKeypad != KeypadState::NO_ACTION)
    return;

  switch (pressedKey)
  {
  case '1':
    currentMenuState = MenuState::CREATE;
    lcdHelper->clearMenuLCD();
    lcdHelper->initInfoLCD();
    break;
  case '2':
    currentMenuState = MenuState::STORAGE;
    lcdHelper->clearMenuLCD();
    lcdHelper->updateInfoLCD();
    break;
  case '3':
    if (currentMenuState != MenuState::CREATE)
      currentMenuState = MenuState::PREVIEW;
    melodyMaker->playDemo();
    break;
  case '6':
    mainMenu();
    break;
  }
}

void handleCreateNavigation()
{
  if (!pressedKey && pressedKeypad != KeypadState::NAVIGATION && pressedKeypad != KeypadState::NO_ACTION)
    return;

  if (pressedKey == '6')
  {
    mainMenu();
  }
}

void mainMenu()
{
  currentMenuState = MenuState::MAIN;
  lcdHelper->initMenuLCD();
  lcdHelper->clearInfoLCD();
  lcdHelper->clearMelodyLCD();
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