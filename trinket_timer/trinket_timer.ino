void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

unsigned long interrupt = millis();
boolean state = false;

void loop() {
  if (millis() > interrupt) {
    interrupt = millis() + 500;
    state = !state;
    digitalWrite(LED_BUILTIN, state);
  }
}
