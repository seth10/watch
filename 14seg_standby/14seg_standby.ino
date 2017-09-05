#include "Adafruit_LEDBackpack.h"

Adafruit_AlphaNum4 alpha4;

unsigned long timeout = millis()+2000;
bool wakeup = false;

void isr() {
  wakeup = true;
}

void setup() {
  pinMode(7, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(7), isr, FALLING);

  alpha4.begin();
  alpha4.writeDigitAscii(0, 'T');
  alpha4.writeDigitAscii(1, 'e');
  alpha4.writeDigitAscii(2, 's');
  alpha4.writeDigitAscii(3, 't', true);
  alpha4.writeDisplay();
}

void loop() {
  if (wakeup) {
      Wire.beginTransmission(0x70);
      Wire.write(0x21); // wake-up
      Wire.endTransmission();
      timeout = millis()+2000;
      wakeup = false;
  }
  if (millis() > timeout) {
    Wire.beginTransmission(0x70);
    Wire.write(0x20); // standby mode
    Wire.endTransmission();
  }
}
