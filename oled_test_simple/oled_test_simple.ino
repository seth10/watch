#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display;

void setup() {
  display.begin();
  // This line is not necessary as I've removed the Adafruit image from the
  // initial buffer in the copy of the library distributed with this repository.
  //display.clearDisplay();

  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Hello, world!");
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.println(3.141592);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("0x"); display.println(0xDEADBEEF, HEX);
  display.display();
  display.startscrollright(0x01, 0x01);
}

void loop() {}
