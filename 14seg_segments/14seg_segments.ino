#include "Adafruit_LEDBackpack.h"

Adafruit_AlphaNum4 alpha4;

void setup() {
  alpha4.begin();
  alpha4.setBrightness(0);
}

void loop() {
  for (uint8_t i=0; i<16; i++) {
    alpha4.writeDigitRaw(0, 1<<i);
    alpha4.writeDigitAscii(2, '0'+i/10);
    alpha4.writeDigitAscii(3, '0'+i%10);
    alpha4.writeDisplay();
    delay(500);
  }
}
