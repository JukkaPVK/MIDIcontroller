#ifndef MIDIencMulti_h
#define MIDIencMulti_h

#include "Arduino.h"
#include "Bounce.h"
#include "Encoder.h"

#define PER_VALUE 1
#define PER_DETENT 4

#define ENCODER 0
#define JOG_1_CC 1
#define JOG_2_CC 2

extern byte MIDIchannel;

class MIDIencMulti{
  public:
    // default constructor
    MIDIencMulti();

    // destructor
    ~MIDIencMulti();

    void initAsEncoder(int a, int b, byte num, byte min, byte max, byte detentOrValue);
    void initAsEncoder(int a, int b, byte num, byte numS, byte min, byte max, byte detentOrValue);
    void initAsJog1Cc(int a, int b, byte num, byte outValLeft, byte outValRight, byte detentOrValue);
    void initAsJog1Cc(int a, int b, byte num, byte numS, byte outValLeft, byte outValRight, byte detentOrValue);
    void initAsJog2Cc(int a, int b, byte numLeft, byte numRight, byte detentOrValue);
    void initAsJog2Cc(int a, int b, byte numLeft, byte numRight, byte numLeftS, byte numRightS, byte detentOrValue);
    int read(); // read input and return a MIDI value (or -1 if none)
    int send(int shiftState = 0); // calls read(), sends and returns a MIDI value (or -1 if none)
    byte numberLeft, numberRight;
    byte numberLeftS, numberRightS;
    byte outValueLeft, outValueRight;
    byte number, numberS;
    byte value;
    byte outLo, outHi;
    byte detentOrValue;
    byte encoderMode;
    Encoder *myKnob;
    void setControlNumber(byte num);
    void outputRange(byte min, byte max);
};

#endif