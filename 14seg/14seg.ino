#include "Adafruit_LEDBackpack.h"
Adafruit_AlphaNum4 alpha4;

volatile byte halfSeconds = 0,
              minutes = 30,
              hours = 9;
volatile boolean blinkSeconds = true;

ISR (TIMER1_OVF_vect) {
  halfSeconds++;
  if (halfSeconds == 120) {
    halfSeconds = 0;
    minutes++;
    if (minutes == 60) {
      minutes = 0;
      hours++;
      if (hours == 24) {
        hours = 0;
      }
    }
  }
  if (halfSeconds%2 == 0)
    blinkSeconds = !blinkSeconds;
}

void setup() {
  // set divider bits of Timer1 to PCK/4096, which is 2Hz at the 8MHz clock rate
  // http://www.atmel.com/Images/Atmel-2586-AVR-8-bit-Microcontroller-ATtiny25-ATtiny45-ATtiny85_Datasheet.pdf#page=90
  TCCR1 |= _BV(CS13) | _BV(CS12);
  // enable Timer/Counter1 overflow interrupt
  TIMSK |= _BV(TOIE1);

  alpha4.begin();
  alpha4.setBrightness(0);
}

void loop() {
  if (hours < 10)
    alpha4.writeDigitAscii(0, ' ');
  else
    alpha4.writeDigitAscii(0, '0'+(hours/10), hours>=12);
  alpha4.writeDigitAscii(1, '0'+(hours%10), true);
  alpha4.writeDigitAscii(2, '0'+(minutes/10));
  alpha4.writeDigitAscii(3, '0'+(minutes%10), blinkSeconds);
  alpha4.writeDisplay();
}
