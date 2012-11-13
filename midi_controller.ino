/*
 MIDI note player
 
 This sketch shows how to use the serial transmit pin (pin 1) to send MIDI note data.
 If this circuit is connected to a MIDI synth, it will play 
 the notes F#-0 (0x1E) to F#-5 (0x5A) in sequence.

 
 The circuit:
 * digital in 1 connected to MIDI jack pin 5
 * MIDI jack pin 2 connected to ground
 * MIDI jack pin 4 connected to +5V through 220-ohm resistor
 Attach a MIDI cable to the jack, then to a MIDI synth, and play music.

 created 13 Jun 2006
 modified 13 Aug 2012
 by Tom Igoe 

 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/Midi
 
 */

//define where your pins are
int latchPin = 8;
int dataPin = 9;
int clockPin = 7;

int special = 2;

//Define variables to hold the data 
//for shift register.
//starting with a non-zero numbers can help
//troubleshoot
byte switchVar1 = 72;  //01001000
 
int midiNote[] = {
 0x35, 0x36, 0x37, 0x38, 0x39, 0x40, 0x41}; 

int state = HIGH;
int specialState = LOW;

void setup() {
  //  Set MIDI baud rate:
  Serial.begin(31250);
  //Serial.begin(9600);
  
  //define pin modes
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT); 
  pinMode(dataPin, INPUT);
  pinMode(special, INPUT);
}

void loop() {
  //Pulse the latch pin:
  //set it to 1 to collect parallel data
  digitalWrite(latchPin,1);
  //set it to 1 to collect parallel data, wait
  delayMicroseconds(20);
  //set it to 0 to transmit data serially  
  digitalWrite(latchPin,0);
  
  specialState = digitalRead(special);
  //Serial.println(specialState);
  
  //while the shift register is in serial mode
  //collect each shift register into a byte
  //the register attached to the chip comes in first 
  switchVar1 = shiftIn(dataPin, clockPin);
  if(state != switchVar1) {
    state = switchVar1;
  
    // debug
    //Serial.println(switchVar1, BIN);
    
    switch (switchVar1) {
      case 0B00000001:
        if(specialState == LOW)
        {
          noteOn(0x90, 0x35, 0x45);
          noteOn(0xb0, 0x6e, 0x00);
        }
        else
          noteOn(0x90, 0x39, 0x45);
        break;
      case 0B00000010:
        if(specialState == LOW)
        {
          noteOn(0x90, 0x36, 0x45);
          noteOn(0xb0, 0x6e, 0x00);
        }
        else
          noteOn(0x90, 0x3a, 0x45);
        break;
      case 0B00000100:
        if(specialState == LOW) 
        {
          noteOn(0x90, 0x37, 0x45);
          noteOn(0xb0, 0x6e, 0x7f);
        }
        else
          noteOn(0x90, 0x3b, 0x45);
        break;
      case 0B00001000:
        if(specialState == LOW)
        {
          noteOn(0x90, 0x38, 0x45);
          noteOn(0xb0, 0x6e, 0x7f);
        }
        else
          noteOn(0x90, 0x3c, 0x45);
        break;
      default:
        break;
    }
  }
  delay(10);
}

//  plays a MIDI note.  Doesn't check to see that
//  cmd is greater than 127, or that data values are  less than 127:
void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}

byte shiftIn(int myDataPin, int myClockPin) { 
  int i;
  int temp = 0;
  int pinState;
  byte myDataIn = 0;

  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, INPUT);
//we will be holding the clock pin high 8 times (0,..,7) at the
//end of each time through the for loop

//at the begining of each loop when we set the clock low, it will
//be doing the necessary low to high drop to cause the shift
//register's DataPin to change state based on the value
//of the next bit in its serial information flow.
//The register transmits the information about the pins from pin 7 to pin 0
//so that is why our function counts down
  for (i=7; i>=0; i--)
  {
    digitalWrite(myClockPin, 0);
    delayMicroseconds(0.2);
    temp = digitalRead(myDataPin);
    if (temp) {
      pinState = 1;
      //set the bit to 0 no matter what
      myDataIn = myDataIn | (1 << i);
    }
    else {
      //turn it off -- only necessary for debuging
     //print statement since myDataIn starts as 0
      pinState = 0;
    }

    //Debuging print statements
    //Serial.print(pinState);
    //Serial.print("     ");
    //Serial.println (dataIn, BIN);

    digitalWrite(myClockPin, 1);

  }
  //debuging print statements whitespace
  //Serial.println();
  //Serial.println(myDataIn, BIN);
  return myDataIn;
}
