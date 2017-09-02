#include "Adafruit_LEDBackpack.h"
Adafruit_AlphaNum4 alpha4;

volatile byte minutes = 30, hours = 9;

void setup() {
  alpha4.begin();
  alpha4.setBrightness(0);
}

void loop() {
  if (hours < 10)
    alpha4.writeDigitAscii(0, ' ');
  else
    alpha4.writeDigitAscii(0, '0'+(hours/10));
  alpha4.writeDigitAscii(1, '0'+(hours%10));
  alpha4.writeDigitAscii(2, '0'+(minutes/10));
  alpha4.writeDigitAscii(3, '0'+(minutes%10));
  alpha4.writeDisplay();
}
