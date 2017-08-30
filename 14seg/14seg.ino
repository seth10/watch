#include "Adafruit_LEDBackpack.h"

Adafruit_AlphaNum4 alpha4;

void setup() {
  alpha4.begin();
  alpha4.writeDigitAscii(0, 'B');
  alpha4.writeDigitAscii(1, 'r');
}

void loop() {
  for (uint8_t b=0; b<16; b++) {
    alpha4.setBrightness(b);
    alpha4.writeDigitAscii(2, '0'+b/10);
    alpha4.writeDigitAscii(3, '0'+b%10);
    alpha4.writeDisplay();
    delay(500);
  }
}
