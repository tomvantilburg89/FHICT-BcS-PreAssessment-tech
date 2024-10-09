#ifndef MELODY_MAKER_H
#define MELODY_MAKER_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Global.h"

extern const int demoFreq[];
extern const int demoLen[];

extern const int BUZZER_PIN;
extern const float BASE_FREQUENCY;
extern const unsigned int MAX_MELODY_LENGTH;

class Melody
{
public:
    Melody(int bpm);
    ~Melody();

    // Melody fields
    unsigned int length();
    unsigned int position();

    // Media controls
    void playMelody();
    void stopMelody();
    void pauseMelody();
    void clearMelody();

    // Sound generation
    void sound(float frequency, int length);
    void debug(char *message, String value);

    // Demo sound
    void loadDemo();
    void playDemo();

    // Misc controls
    void changeBpm();
    void transpose();

    // Get melody values
    int getNoteIndex();
    int getMelodyNoteLengths();
    float getMelodyFrequencies();

    // Media create/etdit/delete
    void add(int noteIndex, int length);
    void remove(int melodyIndex);
    void navigate(bool direction);

    // Helpers
    int getKeyPress(char keypad);
    void setNoteFrequency(int noteIndex); // perhaps do thison push
    void setNoteLength(int noteLength);
    void setPlaybackSpeed();

    const char *getNoteName()
    {
        return this->noteMap[this->keyPressIndex];
    }

    //
    float calculateFrequency(int noteIndex)
    {
        return BASE_FREQUENCY * pow(2, noteIndex / 12.0);
    };

private:
    // Initial
    int bpm;
    const int buzzer;
    const char **noteMap;

    const int *demoFrequencies;
    const int *demoNoteLengths;

    unsigned int melodyLength;

    // Input values
    int noteLength;
    int noteSpeed;
    int keyPressIndex;
    float noteFrequency;

    // Create melody vars
    int *noteLengths;
    int *notePlaybackSpeeds;
    float *noteFrequencies;

    int playbackIndex = 0;

    void setKeyPressIndex(int noteIndex);
    void calculatePlaybackSpeed();
    // LCD
};

#endif // MELODY_H
