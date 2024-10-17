#include <Arduino.h>
#include "MelodyMaker.h"
#include "LcdHelper.h"
#include "Global.h"
#include "MenuState.h"

extern LcdHelper *lcdHelper;

Melody::Melody(int bpm)
    : bpm(bpm), buzzer(BUZZER_PIN), noteMap(namedNotesMap),
      demoFrequencies(demoFreq), demoNoteLengths(demoLen)
{
    noteFrequencies = new float[MAX_MELODY_LENGTH];
    noteKeyPresses = new int[MAX_MELODY_LENGTH];
    noteLengths = new int[MAX_MELODY_LENGTH];
}

Melody::~Melody()
{
    this->addLength(4);
    delete[] noteFrequencies;
    delete[] noteLengths;
}
void Melody::sound()
{
    tone(BUZZER_PIN, this->noteFrequency, this->noteSpeed);
    delay(this->noteSpeed);
    noTone(BUZZER_PIN);
    delay(this->noteSpeed);
    lcdHelper->updateInfoNoteLength();
    lcdHelper->updateInfoFrequency();
    lcdHelper->updateInfoNoteName();
    lcdHelper->updateMelodyLCD();
}

void Melody::addLength(int noteTiming)
{
    this->setNoteLength(noteTiming);
}

void Melody::addNote(int noteIndex)
{
    if (this->melodyLength < MAX_MELODY_LENGTH)
    {
        this->setKeyPressIndex(noteIndex);
        this->setNoteFrequency(noteIndex);
        this->calculatePlaybackSpeed();
        this->sound();
        this->push();
        this->melodyLength++;
        this->playIndex++;
        lcdHelper->updateMelodyLCD();
    }
}

void Melody::push()
{
    this->noteKeyPresses[this->melodyLength] = this->keyPressIndex;
    this->noteLengths[this->melodyLength] = this->noteLength;
    this->noteFrequencies[this->melodyLength] = this->noteFrequency;
}

void Melody::playDemo()
{
    if (currentMenuState != MenuState::PREVIEW)
        return;

    lcdHelper->initDemoMenu();
    for (int i = 0; i < 30; i++)
    {
        this->addLength(demoLen[i]);
        this->addNote(demoFreq[i]);
    }

    currentMenuState = MenuState::MAIN;
}

void Melody::setNoteLength(int noteLength)
{
    this->noteLength = 1 << (noteLength % 6);
    lcdHelper->updateInfoNoteLength();
}

void Melody::setNoteFrequency(int noteIndex)
{
    if (noteIndex == -1)
        this->noteFrequency = 0.0;
    else
        this->noteFrequency = this->calculateFrequency(noteIndex);
}

void Melody::start()
{
    currentMenuState = currentMenuState == MenuState::PLAYING ? MenuState::STOPPED : MenuState::PLAYING;
}

void Melody::stop()
{
    currentMenuState = MenuState::CREATE;
    playIndex = 0;
}

void Melody::play()
{
    if (currentMenuState != MenuState::PLAYING)
        return;

    unsigned long currentTime = millis();

    if (playIndex < melodyLength)
    {
        this->keyPressIndex = this->noteKeyPresses[playIndex];
        this->noteLength = this->noteLengths[playIndex];
        this->noteFrequency = this->noteFrequencies[playIndex];
        this->calculatePlaybackSpeed();
        if (currentTime - previousTime >= this->noteSpeed)
        {
            this->sound();
            playIndex++;
        }
    }
    else if (playIndex >= melodyLength)
    {
        playIndex = 0;
        currentMenuState = MenuState::CREATE;
    }
}

// TODO: move this to keybaord handler
int Melody::getKeyPress(char key)
{
    if (!key)
        return -1;

    switch (key)
    {
        // Note / durationkeypad

    case '1': // A4
        return 0;
    case '2': // A#4
        return 1;
    case '3': // B4
        return 2;
    case '4': // C5
        return 3;
    case '5': // C#5
        return 4;
    case '6': // D5
        return 5;
    case '7': // D#5
        return 6;
    case '8': // E5
        return 7;
    case '9': // F5
        return 8;
    case '*': // F#5
        return 9;
    case '0': // G5
        return 10;
    case '#': // G#5
        return 11;
    default:
        return -1;
    }
}

unsigned int Melody::length()
{
    return melodyLength >= 0 && melodyLength < MAX_MELODY_LENGTH ? melodyLength : -1;
}

void Melody::remove(int melodyIndex)
{
}

void Melody::setKeyPressIndex(int noteIndex)
{
    this->keyPressIndex = noteIndex;
}

void Melody::calculatePlaybackSpeed()
{

    switch (this->noteLength)
    {
    case 1:
        this->noteSpeed = (60000 / this->bpm) * 4; // Whole note
        break;
    case 2:
        this->noteSpeed = (60000 / this->bpm) * 2; // Half note
        break;
    case 4:
        this->noteSpeed = (60000 / this->bpm); // Quarter note
        break;
    case 8:
        this->noteSpeed = (60000 / this->bpm) / 2; // Eighth note
        break;
    case 16:
        this->noteSpeed = (60000 / this->bpm) / 4; // 16th note
        break;
    case 32:
        this->noteSpeed = (60000 / this->bpm) / 8; // 32th note
        break;
    default:
        break;
    }
}

int Melody::getBpm()
{
    return this->bpm;
}

void Melody::increaseBpm()
{
    this->bpm += 10;
    lcdHelper->updateInfoBpm();
}

void Melody::decreaseBpm()
{
    if (this->bpm > 20)
    {
        this->bpm -= 10;
        lcdHelper->updateInfoBpm();
    }
}

float Melody::getNoteFrequency()
{
    return this->noteFrequency;
}

int Melody::getNoteLength()
{
    return this->noteLength;
}

const char *Melody::getNoteName()
{
    if (this->noteFrequency == 0.0)
    {
        return ".";
    }
    return this->noteMap[this->keyPressIndex];
}

//
float Melody::calculateFrequency(int noteIndex)
{

    return BASE_FREQUENCY * pow(2, noteIndex / 12.0);
};