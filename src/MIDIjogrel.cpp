
#include "MIDIjogRel.h"

// constructors
MIDIjogRel::MIDIjogRel(){};

MIDIjogRel::MIDIjogRel(int a, int b, byte num, byte outValLeft, byte outValRight, byte detentOrValue){
  myKnob = new Encoder(a, b);
	number = num;
  outValueLeft = outValLeft;
  outValueRight = outValRight;
  this->detentOrValue = detentOrValue; // Rotation detected per encoder value or detent
  value = 0;
};

MIDIjogRel::MIDIjogRel(int a, int b, byte num, byte numS, byte outValLeft, byte outValRight, byte detentOrValue){
  myKnob = new Encoder(a, b);
	number = num;
  numberS = numS;
  outValueLeft = outValLeft;
  outValueRight = outValRight;
  this->detentOrValue = detentOrValue; // Rotation detected per encoder value or detent
  value = 0;
};

// destructor
MIDIjogRel::~MIDIjogRel(){
  delete myKnob;
};

int MIDIjogRel::read(){
  int newValue = myKnob->read();
  newValue = newValue / detentOrValue;
  return newValue;
}

int MIDIjogRel::send(int shiftState){
  int newValue = read();
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
