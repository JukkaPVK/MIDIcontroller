#ifndef MIDIjog_h
#define MIDIjog_h

#include "Arduino.h"
#include "Bounce.h"
#include "Encoder.h"

#define PER_VALUE 1
#define PER_DETENT 4
extern byte MIDIchannel;

class MIDIjog{
  public:
    // default constructor
    MIDIjog();
    
    // constructor when only pins and control numbers (left/right turn) are given
    MIDIjog(int a, int b, byte numLeft, byte numRight);
    
    // " pins, control numbers (left/right turn) and whether value changes PER_DETENT or PER_VALUE
    MIDIjog(int a, int b, byte numLeft, byte numRight, byte detentOrValue);
  
   
    // destructor
    ~MIDIjog();

    int read(); // read input and return a MIDI value (or 0 if none)
    int send(); // calls read(), sends and returns a MIDI value (or 0 if none)
    byte numberLeft;
    byte numberRight;
    byte value;
    byte outLo, outHi;
    byte detentOrValue;
    Encoder *myKnob;
    void setControlNumberLeft(byte numLeft);
    void setControlNumberRight(byte numRight);
};

#endif