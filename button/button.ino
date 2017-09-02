#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display;

volatile int n = 0;

void isr() {
  n++;
}

void setup() {
  Serial.begin(9600);
  pinMode(7, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(7), isr, FALLING);
  display.begin();
  display.setTextSize(8);
  display.setTextColor(WHITE);
}

void loop() {
  display.clearDisplay();
  display.setCursor((128-(8*5))/2, 0);
  display.println(n);
  display.display();
  delay(50);
}
