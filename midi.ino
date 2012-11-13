//  plays a MIDI note.  Doesn't check to see that
//  cmd is greater than 127, or that data values are  less than 127:

basePitch = 0x34;
velocity = 0x7f;

void noteOn(int offset) {
    Serial.write(0x90);
    Serial.write(basePitch + offset);
    Serial.write(velocity);
}

void sliderLeft() {
    Serial.write(0xb0);
    Serial.write(0x6e);
    Serial.write(0x00);
}

void sliderRight() {
    Serial.write(0xb0);
    Serial.write(0x6e);
    Serial.write(0x7f);
}
