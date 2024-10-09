#include <Arduino.h>
#include "MelodyMaker.h"
#include "Global.h"

Melody::Melody(int bpm)
    : bpm(bpm), buzzer(BUZZER_PIN), noteMap(namedNotesMap),
      demoFrequencies(demoFreq), demoNoteLengths(demoLen)
{
    noteFrequencies = new float[MAX_MELODY_LENGTH];
    noteLengths = new int[MAX_MELODY_LENGTH];
}

Melody::~Melody()
{
    delete[] noteFrequencies;
    delete[] noteLengths;
}
void Melody::loadDemo()
{

    for (int i = 0; i < 30; i++)
    {
        this->add(demoFreq[i], demoLen[i]);
    }
}

void Melody::sound(float frequency, int speed)
{
    tone(BUZZER_PIN, frequency, speed);
    delay(speed);
    noTone(BUZZER_PIN);
    delay(speed);
}

void Melody::add(int noteIndex, int length)
{
    if (this->melodyLength < MAX_MELODY_LENGTH)
    {
        this->setKeyPressIndex(noteIndex);
        this->setNoteFrequency(noteIndex);
        this->setNoteLength(length);
        this->calculatePlaybackSpeed();

        this->sound(this->noteFrequency, this->noteSpeed / 1.2);

        this->melodyLength++;
    }
}

void Melody::setNoteLength(int noteLength)
{
    this->noteLength = 1 << (noteLength % 6);
}

void Melody::setNoteFrequency(int noteIndex)
{
    this->noteFrequency = this->calculateFrequency(noteIndex);
}

void Melody::playMelody()
{
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
    int bpm = this->bpm;

    switch (this->noteLength)
    {
    case 1:
        this->noteSpeed = (60000 / bpm) * 4; // Whole note
        break;
    case 2:
        this->noteSpeed = (60000 / bpm) * 2; // Half note
        break;
    case 4:
        this->noteSpeed = (60000 / bpm); // Quarter note
        break;
    case 8:
        this->noteSpeed = (60000 / bpm) / 2; // Eighth note
        break;
    case 16:
        this->noteSpeed = (60000 / bpm) / 4; // 16th note
        break;
    default:
        break;
    }
}