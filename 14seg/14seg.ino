#include "Adafruit_LEDBackpack.h"
Adafruit_AlphaNum4 alpha4;

volatile byte minutes = 30, hours = 9;

unsigned long nextHalfMinuteUpdate = millis()+30*1000;
boolean halfMinute = false;

void setup() {
  alpha4.begin();
  alpha4.setBrightness(0);
}

void loop() {
  if (millis() > nextHalfMinuteUpdate) {
    nextHalfMinuteUpdate += 30*1000;
    halfMinute = !halfMinute;
    if (!halfMinute) {
      minutes++;
      if (minutes == 60) {
        minutes = 0;
        hours++;
        if (hours == 24) hours = 0;
      }
    }
  }

  if (hours < 10)
    alpha4.writeDigitAscii(0, ' ');
  else
    alpha4.writeDigitAscii(0, '0'+(hours/10), hours>=12);
  alpha4.writeDigitAscii(1, '0'+(hours%10), true);
  alpha4.writeDigitAscii(2, '0'+(minutes/10));
  alpha4.writeDigitAscii(3, '0'+(minutes%10));
  alpha4.writeDisplay();
}
