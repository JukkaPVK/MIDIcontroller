/*FIXME: after the value bottoms out alternating MIDI messages (0 1 0 1 0...)
  will occasionally continue to be sent.
*/

#include "MIDIenc.h"

// constructors
MIDIenc::MIDIenc(){};

MIDIenc::MIDIenc(int a, int b, byte num){
  myKnob = new Encoder(a, b);
	number = num;
  detentOrValue = 1; // CC changes once per encoder value
  value = 0;
  outLo = 0;
  outHi = 127;
};

MIDIenc::MIDIenc(int a, int b, byte num, byte detentOrValue){
  myKnob = new Encoder(a, b);
	number = num;
  this->detentOrValue = detentOrValue; // CC changes per encoder value or detent
  value = 0;
  outLo = 0;
  outHi = 127;
};

MIDIenc::MIDIenc(int a, int b, byte num, byte min, byte max){
  myKnob = new Encoder(a, b);
	number = num;
  detentOrValue = 1; // CC changes once per encoder value
  value = 0;
  outLo = min;
  outHi = max;
};

MIDIenc::MIDIenc(int a, int b, byte num, byte min, byte max, byte detentOrValue){
  myKnob = new Encoder(a, b);
	number = num;
  this->detentOrValue = detentOrValue; // CC changes per encoder value or detent
  value = 0;
  outLo = min;
  outHi = max;
};

// destructor
MIDIenc::~MIDIenc(){
  delete myKnob;
};

int MIDIenc::read(){
  int newValue;
  newValue = myKnob->read();
  newValue = newValue / detentOrValue;
  if(newValue >= outLo && newValue <= outHi){
    return newValue;
  }
  else {
    myKnob->write(value * detentOrValue); // Write original value to knob, to prevent running over outHi
    return value;  // return original value, since no changes
    }
}

int MIDIenc::send(){
  int newValue = read();
    if (newValue != value) {
      usbMIDI.sendControlChange(number, newValue, MIDIchannel);
      value = newValue;
    }
  return newValue;
}

// Set the CC number.
void MIDIenc::setControlNumber(byte num){
  number = num;
};

// Set upper and lower limits for outgoing MIDI messages.
void MIDIenc::outputRange(byte min, byte max){
  outLo = min;
  outHi = max;
};
