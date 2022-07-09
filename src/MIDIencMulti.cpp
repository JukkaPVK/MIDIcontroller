#include "MIDIencMulti.h"

// constructor
MIDIencMulti::MIDIencMulti(){};

// destructor
MIDIencMulti::~MIDIencMulti(){
  delete myKnob;
};
// Init without internal shift
void MIDIencMulti::initAsEncoder(int a, int b, byte num, byte min, byte max, byte detentOrValue){
  myKnob = new Encoder(a, b);
	number = num;
  this->detentOrValue = detentOrValue; // CC changes per encoder value or detent
  value = 0;
  outLo = min;
  outHi = max;
  encoderMode = 0;
};
// Init with internal shift
void MIDIencMulti::initAsEncoder(int a, int b, byte num, byte numS, byte min, byte max, byte detentOrValue){
  myKnob = new Encoder(a, b);
	number = num;
  numberS = numS;
  this->detentOrValue = detentOrValue; // CC changes per encoder value or detent
  value = 0;
  outLo = min;
  outHi = max;
  encoderMode = 0;
};

// Init without internal shift
void MIDIencMulti::initAsJog1Cc(int a, int b, byte num, byte outValLeft, byte outValRight, byte detentOrValue){
  myKnob = new Encoder(a, b);
	number = num;
  outValueLeft = outValLeft;
  outValueRight = outValRight;
  this->detentOrValue = detentOrValue; // Rotation detected per encoder value or detent
  value = 0;
  encoderMode = 1;
};
// Init with internal shift
void MIDIencMulti::initAsJog1Cc(int a, int b, byte num, byte numS, byte outValLeft, byte outValRight, byte detentOrValue){
  myKnob = new Encoder(a, b);
	number = num;
  numberS = numS;
  outValueLeft = outValLeft;
  outValueRight = outValRight;
  this->detentOrValue = detentOrValue; // Rotation detected per encoder value or detent
  value = 0;
  encoderMode = 1;
};

// Init without internal shift
void MIDIencMulti::initAsJog2Cc(int a, int b, byte numLeft, byte numRight, byte detentOrValue){
  myKnob = new Encoder(a, b);
	numberLeft = numLeft;
  numberRight = numRight;
  this->detentOrValue = detentOrValue; // Rotation detected per encoder value or detent
  value = 0;
  outLo = 0;
  outHi = 127;
  encoderMode = 2;
};

// Init with internal shift
void MIDIencMulti::initAsJog2Cc(int a, int b, byte numLeft, byte numRight,  byte numLeftS, byte numRightS, byte detentOrValue){
  myKnob = new Encoder(a, b);
	numberLeft = numLeft;
  numberRight = numRight;
	numberLeftS = numLeftS;
  numberRightS = numRightS;
  this->detentOrValue = detentOrValue; // Rotation detected per encoder value or detent
  value = 0;
  outLo = 0;
  outHi = 127;
  encoderMode = 2;
};


int MIDIencMulti::read(){
  if (encoderMode == 0) {
    int newValue = -1;
    int incdec = myKnob->read();
    if (incdec >= detentOrValue ) {
      if (value < outHi ){
        newValue = value + 1;
      }
      myKnob->write(0);
    }
    else if (incdec <= -detentOrValue) {
      if (value > outLo){
        newValue = value - 1;
      }
      myKnob->write(0);
    }
    else {
      newValue = -1;
    }
    return newValue;
  }
  else {
      int newValue = myKnob->read();
      newValue = newValue / detentOrValue;
      return newValue;
  }
};

int MIDIencMulti::send(int shiftState){
  int newValue = read();
  if (encoderMode == 0) {
    if (newValue >= 0){
      if (shiftState == 1) {
        usbMIDI.sendControlChange(numberS, newValue, MIDIchannel);
      }
      else {
        usbMIDI.sendControlChange(number, newValue, MIDIchannel);
      }
      value = newValue;
    }
    return newValue;
  }
  else if (encoderMode == 1) {
    if (newValue != 0) {
      if (newValue > 0) {
        if (shiftState == 1) {
          usbMIDI.sendControlChange(numberS, outValueRight, MIDIchannel);
        } 
        else {
          usbMIDI.sendControlChange(number, outValueRight, MIDIchannel);
        }          
      }
      else if (newValue < 0 ) {
        if (shiftState == 1) {
          usbMIDI.sendControlChange(numberS, outValueLeft, MIDIchannel);
        }
        else {
          usbMIDI.sendControlChange(number, outValueLeft, MIDIchannel);
        }
      }
      myKnob->write(0);
    }
    return newValue;
  }
  else {
    if (newValue != 0) {
      if (newValue > 0) {
        if (shiftState == 1) {
          usbMIDI.sendControlChange(numberRightS, outHi, MIDIchannel);
        } 
        else {
          usbMIDI.sendControlChange(numberRight, outHi, MIDIchannel);
        }       
      }
      else if (newValue < 0 ) {
        if (shiftState == 1) {
          usbMIDI.sendControlChange(numberLeftS, outHi, MIDIchannel);
        }
        else {
          usbMIDI.sendControlChange(numberLeft, outHi, MIDIchannel);
        }
      }
      myKnob->write(0);
    }
    return newValue;
  }
}

// Set the CC number.
void MIDIencMulti::setControlNumber(byte num){
  number = num;
};

// Set upper and lower limits for outgoing MIDI messages.
void MIDIencMulti::outputRange(byte min, byte max){
  outLo = min;
  outHi = max;
};