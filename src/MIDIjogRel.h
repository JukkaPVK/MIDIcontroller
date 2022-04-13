#ifndef MIDIjogRel_h
#define MIDIjogRel_h

#include "Arduino.h"
#include "Bounce.h"
#include "Encoder.h"

#define PER_VALUE 1
#define PER_DETENT 4
extern byte MIDIchannel;

class MIDIjogRel{
  public:
    // default constructor
    MIDIjogRel();

    // " pins, control number, values for left/right turn and whether value changes PER_DETENT or PER_VALUE
    MIDIjogRel(int a, int b, byte num, byte outValLeft, byte outValRight, byte detentOrValue);

    // constructor when only pins, control number and values for left/right (+Shift) turn are given and whether value changes PER_DETENT or PER_VALUE
    MIDIjogRel(int a, int b, byte num, byte numS, byte outValLeft, byte outValRight, byte detentOrValue);
    
   
    // destructor
    ~MIDIjogRel();

    int read(); // read input and return a MIDI value (or 0 if none)
    int send(int shiftState = 0); // calls read(), sends and returns a MIDI value (or 0 if none)
    byte number;
    byte numberS;
    byte value;
    byte outValueLeft, outValueRight;
    byte detentOrValue;
    Encoder *myKnob;
};

#endif