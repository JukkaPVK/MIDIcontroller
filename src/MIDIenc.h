#ifndef MIDIenc_h
#define MIDIenc_h

#include "Arduino.h"
#include "Bounce.h"
#include "Encoder.h"

#define PER_VALUE 1
#define PER_DETENT 4
extern byte MIDIchannel;

class MIDIenc{
  public:
    // default constructor
    MIDIenc();
    
    // constructor when only pins and control number are given
    MIDIenc(int a, int b, byte num);
    
    // " pins, control number and whether value changes PER_DETENT or PER_VALUE
    MIDIenc(int a, int b, byte num, byte detentOrValue);

    // " pins, control number and whether value changes PER_DETENT or PER_VALUE
    MIDIenc(int a, int b, byte num, byte numS, byte detentOrValue);

    // " pins, control number, minimum and maximum outgoing MIDI values set
    MIDIenc(int a, int b, byte num, byte min, byte max, byte detentOrValue);
    
    // " pins, control number, min, max and PER_VALUE/PER_DETENT
    MIDIenc(int a, int b, byte num, byte numS ,byte min, byte max, byte detentOrValue);

    // destructor
    ~MIDIenc();

    int read(); // read input and return a MIDI value (or -1 if none)
    int send(int shiftState = 0); // calls read(), sends and returns a MIDI value (or -1 if none)
    byte number;
    byte numberS;
    byte value;
    byte outLo, outHi;
    byte detentOrValue;
    Encoder *myKnob;
    void setControlNumber(byte num);
    void outputRange(byte min, byte max);
};

#endif