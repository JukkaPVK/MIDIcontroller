
#include "MIDIjog.h"

// constructors
MIDIjog::MIDIjog(){};

MIDIjog::MIDIjog(int a, int b, byte numLeft, byte numRight){
  myKnob = new Encoder(a, b);
	numberLeft = numLeft;
    numberRight = numRight;
  detentOrValue = 1; // Rotation detected once per encoder value
  value = 0;
  outLo = 0;
  outHi = 127;
};

MIDIjog::MIDIjog(int a, int b, byte numLeft, byte numRight, byte detentOrValue){
  myKnob = new Encoder(a, b);
	numberLeft = numLeft;
  numberRight = numRight;
  this->detentOrValue = detentOrValue; // Rotation detected per encoder value or detent
  value = 0;
  outLo = 0;
  outHi = 127;
};

// destructor
MIDIjog::~MIDIjog(){
  delete myKnob;
};

int MIDIjog::read(){
  int newValue = myKnob->read();
  newValue = newValue / detentOrValue;
  return newValue;
}

int MIDIjog::send(){
  int newValue = read();
      if (newValue != 0) {
          if (newValue > 0) {
            usbMIDI.sendControlChange(numberRight, outHi, MIDIchannel);
            myKnob->write(0);
            
          }
          else if (newValue < 0 ) {
            usbMIDI.sendControlChange(numberLeft, outHi, MIDIchannel);
            myKnob->write(0);
         }
      }
  return newValue;
}

// Set the CC numbers for left and right turn.
void MIDIjog::setControlNumberLeft(byte numLeft){
  numberLeft = numLeft;
};

void MIDIjog::setControlNumberRight(byte numRight){
  numberRight = numRight;
};
