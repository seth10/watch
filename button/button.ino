volatile int n = 0;

void isr() {
  Serial.println(millis());
  n++;
}

void setup() {
  Serial.begin(9600);
  pinMode(7, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(7), isr, FALLING);
}

void loop() {
  Serial.println(n);
  delay(200);
}
