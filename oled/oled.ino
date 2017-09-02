#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display;

volatile byte minutes = 30, hours = 9;

volatile unsigned long lastISR = 0;
volatile unsigned long delta;
volatile byte sequence = 0;

void isr() {
  delta = millis() - lastISR;
  lastISR = millis();
  if (delta < 100) return; // debounce

  /**/ if (delta > 4000) sequence = 0;
  else if (delta > 3000) sequence = 3;
  else if (delta > 2000) sequence = 2;
  else if (delta > 1000) sequence = 1;

  switch (sequence) {
    case 1: minutes = (minutes+1)  % 60; break;
    case 2: minutes = (minutes+10) % 60; break;
    case 3: hours   = (hours+1)    % 24; break;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(7, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(7), isr, FALLING);
  display.begin();
  display.setTextColor(WHITE);
}

void loop() {
  display.clearDisplay();
  display.setCursor(0, 14);
  display.setTextSize(4);
  if ((hours%12) < 10 && (hours%12) > 0) display.print(' ');
  display.print(((hours+11)%12)+1);
  display.print(':');
  if (minutes < 10) display.print('0');
  display.print(minutes);
  //display.setCursor(128-(12*2), 64-14);
  display.setCursor(104, 50);
  display.setTextSize(2);
  if (hours < 12)
    display.print("AM");
  else
    display.print("PM");
  display.display();
}
