#ifndef MELODY_MAKER_H
#define MELODY_MAKER_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Global.h"

extern const int demoFreq[];
extern const int demoLen[];

extern const int BUZZER_PIN;
extern const float BASE_FREQUENCY;
extern const int MAX_MELODY_LENGTH;

class Melody
{
public:
    Melody(int bpm);
    ~Melody();

    // Melody fields
    unsigned int length();

    // Media controls
    void play();
    void stopMelody();
    void pauseMelody();
    void clearMelody();

    void push();

    // Sound generation
    void sound(float frequency, int speed);
    void debug(char *message, String value);

    // Demo sound
    void playDemo();

    // Misc controls
    void changeBpm();
    void transpose();

    // Get melody values
    int getNoteIndex();
    int getMelodyNoteLengths();
    float getMelodyFrequencies();
    int playIndex = 0;

    int melodyLength = 0;

    // Media create/etdit/delete
    void addNote(int noteIndex);
    void addLength(int noteLength);
    void position(int index);
    void remove(int melodyIndex);
    void navigate(bool direction);

    // Helpers
    int getKeyPress(char keypad);

    void setNoteFrequency(int noteIndex); // perhaps do thison push
    void setNoteLength(int noteLenght);

    void setPlaybackSpeed();

    int getBpm();
    void increaseBpm();
    void decreaseBpm();

    float getNoteFrequency();

    int getNoteLength();

    const char *getNoteName();

    //
    float calculateFrequency(int noteIndex);

private:
    // Initial
    int bpm;
    const int buzzer;
    const char **noteMap;

    const int *demoFrequencies;
    const int *demoNoteLengths;

    // Input values
    int noteLength = 16;
    int noteSpeed = (60000 / this->bpm) / 8;
    int keyPressIndex;
    float noteFrequency = 440.0;

    // Create melody vars
    int *noteLengths;
    int *noteKeyPresses;
    int *noteSpeeds;
    float *noteFrequencies;

    /// playback
    unsigned long previousTime;
    unsigned long timeBouceDelay = 50;
    int currentNoteLength = 0;


    void setKeyPressIndex(int noteIndex);
    void calculatePlaybackSpeed();
    // LCD
};

#endif // MELODY_H
