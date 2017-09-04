#include <Wire.h>

const byte INIT_SEQUENCE[] = {0xAE, 0xD5, 0x80, 0xA8, 0x3F, 0xD3, 0x00, 0x40,
    0x8D, 0x14, 0x20, 0x00, 0xA1, 0xC8, 0xDA, 0x12, 0x81, 0xCF, 0xD9, 0xF1,
    0xDB, 0x40, 0xA4, 0xA6, 0x2E, 0xAF, 0x21, 0x00, 0x7F, 0x22, 0x00, 0x07};

void command(uint8_t c) {
  Wire.beginTransmission(0x3C);
  Wire.write(0x80);
  Wire.write(c);
  Wire.endTransmission();
}
void data(uint8_t d) {
  Wire.beginTransmission(0x3C);
  Wire.write(0x40);
  Wire.write(d);
  Wire.endTransmission();
}

void setup() {
  Wire.begin();
  for (uint8_t i=0; i<32; i++)
    command(INIT_SEQUENCE[i]);

  for (uint16_t i=0; i<128*8; i++)
    data(i);

  // clear columns 47-92 on page 3 (random numbers)
  command(0x21);
  command(47);
  command(92);
  command(0x22);
  command(3);
  command(3);
  for (uint8_t i=0; i<(92-47+1)*(3-3+1); i++)
    data(0xFF);
}

void loop() {}
