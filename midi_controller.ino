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
byte switchVar2 = 72;
 
int state1 = HIGH;
int state2 = HIGH;
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
  swicthVar2 = shiftIn(dataPin, clockPin);

  if(state1 != switchVar1 || state2 != switchVar2) {
    state1 = switchVar1;
    state2 = switchVar2;
  
    // debug
    //Serial.println(switchVar1, BIN);
    //Serial.println(switchVar2, BIN);
    
    switch (switchVar1) {
      case 0B00000001:
        if(specialState == LOW)
        {
          noteOn(1);
          sliderLeft();
        }
        else
          noteOn(5);
        break;
      case 0B00000010:
        if(specialState == LOW)
        {
          noteOn(2);
          sliderLeft();
        }
        else
          noteOn(6);
        break;
      case 0B00000100:
        if(specialState == LOW) 
        {
          noteOn(3);
          sliderRight();
        }
        else
          noteOn(7);
        break;
      case 0B00001000:
        if(specialState == LOW)
        {
          noteOn(4);
          sliderRight();
        }
        else
          noteOn(8);
        break;
      case 0B00010000:
        if(specialState == LOW)
        {
          noteOn(5);
          sliderRight();
        }
        else
          noteOn(9);
        break;
      case 0B00100000:
        if(specialState == LOW)
        {
          noteOn(6);
          sliderRight();
        }
        else
          noteOn(10);
        break;
      case 0B01000000:
        if(specialState == LOW)
        {
          noteOn(7);
          sliderRight();
        }
        else
          noteOn(11);
        break;
      case 0B10000000:
        if(specialState == LOW)
        {
          noteOn(8);
          sliderRight();
        }
        else
          noteOn(12);
        break;
      default:
        break;
    }

    switch (switchVar2) {
      case 0B00000001:
        if(specialState == LOW)
        {
          noteOn(9);
          sliderLeft();
        }
        else
          noteOn(13);
        break;
      case 0B00000010:
        if(specialState == LOW)
        {
          noteOn(10);
          sliderLeft();
        }
        else
          noteOn(14);
        break;
      case 0B00000100:
        if(specialState == LOW) 
        {
          noteOn(11);
          sliderRight();
        }
        else
          noteOn(15);
        break;
      case 0B00001000:
        if(specialState == LOW)
        {
          noteOn(12);
          sliderRight();
        }
        else
          noteOn(16);
        break;
      case 0B00010000:
        if(specialState == LOW)
        {
          noteOn(13);
          sliderRight();
        }
        else
          noteOn(17);
        break;
      case 0B00100000:
        if(specialState == LOW)
        {
          noteOn(14);
          sliderRight();
        }
        else
          noteOn(18);
        break;
      case 0B01000000:
        if(specialState == LOW)
        {
          noteOn(15);
          sliderRight();
        }
        else
          noteOn(19);
        break;
      case 0B10000000:
        if(specialState == LOW)
        {
          noteOn(16);
          sliderRight();
        }
        else
          noteOn(20);
        break;
      default:
        break;
    }
  }
  delay(10);
}
