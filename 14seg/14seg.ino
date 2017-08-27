#include "Adafruit_LEDBackpack.h"

char *message = "    Hello world!    ";

Adafruit_AlphaNum4 alpha4;

void setup() {
  alpha4.begin();

  for (uint8_t i=0; i<strlen(message)-4; i++) {
    alpha4.writeDigitAscii(0, message[i]);
    alpha4.writeDigitAscii(1, message[i+1]);
    alpha4.writeDigitAscii(2, message[i+2]);
    alpha4.writeDigitAscii(3, message[i+3]);
    alpha4.writeDisplay();
    delay(200);
  }

  alpha4.clear();
  alpha4.writeDisplay();
  delay(1000);
}

void loop() {
  for (uint8_t i=0; i<4; i++) {
    alpha4.writeDigitRaw((i+4-1)%4, 0x0);
    alpha4.writeDigitRaw(i, 0xFFFF);
    alpha4.writeDisplay();
    delay(200);
  }
}
