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
    handleMainNavigation();
    break;
  case KeypadState::TIMINGS:
    if (currentMenuState == MenuState::CREATE)
    {
      melodyMaker->addLength(currentKey);
      if (currentKey > 5)
      {
        melodyMaker->addNote(-1);
        melodyMaker->sound();
        lcdHelper->updateMelodyLCD();
      }
    }
    break;
  case KeypadState::NOTES:
    if (currentMenuState == MenuState::CREATE)
    {

      melodyMaker->addNote(currentKey);
      lcdHelper->updateMelodyLCD();
    }
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
    if (currentMenuState == MenuState::MAIN || currentMenuState == MenuState::CREATE)
    {
      melodyMaker = new Melody(160);
      currentMenuState = MenuState::CREATE;
      lcdHelper->clearMenuLCD();
      lcdHelper->clearInfoLCD();
      lcdHelper->clearMelodyLCD();
      lcdHelper->initCreateMenuLCD();
    }
    break;
  case '3':
    if (currentMenuState == MenuState::MAIN)
    {
      currentMenuState = MenuState::PREVIEW;
      lcdHelper->initInfoLCD();
      melodyMaker->playDemo();
    }
    if (currentMenuState != MenuState::MAIN)
    {
      currentMenuState = MenuState::MAIN;
      mainMenu();
    }
    break;
  case '6':
    break;
  case '7':
    break;
  case '8':
    melodyMaker->increaseBpm();
    break;
  case '9':
    break;
  case '0':
    melodyMaker->decreaseBpm();
    break;
  case '*':
    if (melodyMaker->playIndex == 0)
    {
      lcdHelper->clearMelodyLCD();
    }
    melodyMaker->start();
    break;
  case '#':
    currentMenuState = MenuState::STOPPED;
    lcdHelper->clearMelodyLCD();
    melodyMaker->stop();
    break;
  }
}

void mainMenu()
{

  lcdHelper->clearMenuLCD();
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
    // pressedKeypad = KeypadState::NO_ACTION;

  } while (keyPressed && (currentDebounceTime - lastDebounceTime) < debounceDelay);
}