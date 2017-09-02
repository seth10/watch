#include "Adafruit_LEDBackpack.h"
Adafruit_AlphaNum4 alpha4;

byte seconds = 0,
     minutes = 30,
     hours = 9;
boolean blinkSeconds = true;
unsigned long nextSecond = millis()+1000;

void incrementSeconds() {
  seconds++;
  if (seconds == 60) {
    seconds = 0;
    minutes++;
    if (minutes == 60) {
      minutes = 0;
      hours++;
      if (hours == 24) {
        hours = 0;
      }
    }
  }
  blinkSeconds = !blinkSeconds;
  nextSecond = millis()+1000;
}

void setup() {
  alpha4.begin();
  alpha4.setBrightness(0);
}

void loop() {
  if (millis() > nextSecond) incrementSeconds();

  if (hours < 10)
    alpha4.writeDigitAscii(0, ' ');
  else
    alpha4.writeDigitAscii(0, '0'+(hours/10), hours>=12);
  alpha4.writeDigitAscii(1, '0'+(hours%10), true);
  alpha4.writeDigitAscii(2, '0'+(minutes/10));
  alpha4.writeDigitAscii(3, '0'+(minutes%10), blinkSeconds);
  alpha4.writeDisplay();
}
