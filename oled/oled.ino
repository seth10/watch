#include <TimerOne.h>

#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display;

volatile byte seconds = 0,
              minutes = 30,
              hours = 9;
volatile boolean showColonDelimiter = true;

volatile unsigned long lastISR = 0;
volatile unsigned long delta;
volatile byte sequence = 0;

void handleButton() {
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
  showColonDelimiter = !showColonDelimiter;
}

void setup() {
  Serial.begin(9600);
  pinMode(7, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(7), handleButton, FALLING);

  // Timer1 can only handle up to ~8 seconds, not 60, so isntead count seconds
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(incrementSeconds);

  display.begin();
  display.setTextColor(WHITE);
}

void loop() {
  display.clearDisplay();
  display.setCursor(0, 14);
  display.setTextSize(4);
  byte printHours = ((hours+11)%12)+1;
  if (printHours < 10 ) display.print(' ');
  display.print(printHours);
  if (showColonDelimiter)
    display.print(':');
  else
    display.print(' ');
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
