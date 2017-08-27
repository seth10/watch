#include <Wire.h>

const /*PROGMEM*/ uint16_t INIT_SEQUENCE[] = {0xAE, 0xD5, 0x80, 0xA8, 0x3F, 0xD3,
    0x00, 0x40, 0x8D, 0x14, 0x20, 0x00, 0xA1, 0xC8, 0xDA, 0x12, 0x81, 0xCF, 0xD9,
    0xF1, 0xDB, 0x40, 0xA4, 0xA6, 0x2E, 0xAF, 0x21, 0x00, 0x7F, 0x22, 0x00, 0x07};

void setup() {
  Wire.begin();
  for (uint8_t i=0; i<31; i++) {
    Wire.beginTransmission(0x3C);
    Wire.write(0x80);
    Wire.write(INIT_SEQUENCE[i]);
    Wire.endTransmission();
  }

  Wire.beginTransmission(0x3C);
  Wire.write(0x40);
  for (uint16_t i=0; i<128*8; i++) { // 128 columns by 8 pages
    Wire.write(0x55);
  }
  Wire.endTransmission();
}

void loop() {}
