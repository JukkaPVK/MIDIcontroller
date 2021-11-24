#include "MIDIcontroller.h"

byte MIDIchannel = 5;

// PIN SETUP
const int jog1PinA = 27;  // Change these numbers to
const int jog1PinB = 28;  // the two pins your encoder is on.
const int jog1Btn = 29;   // Change the number to the pin your encoder button is on.


// Create Jogwheel (encoder) objects
// Encoder parameters are: pin A, pin B, CC numbers for left and right turn and optional detent value (1 or 4)
MIDIjog myJog1(jog1PinA, jog1PinB, 21, 22, 4); // Jogwheel (encoder) 1 
MIDIbutton myJog1Btn(jog1Btn, 26, TRIGGER);


void setup(){

}

// Main function
void loop(){

  myJog1.send();
  myJog1Btn.send();

// This prevents crashes that happen when incoming usbMIDI is ignored.
  while(usbMIDI.read()){}

// Also uncomment this if compiling for standard MIDI
//  while(MIDI.read()){}
}
