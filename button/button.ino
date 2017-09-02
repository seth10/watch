volatile int n = 0;

void isr() {
  n++;
}

void setup() {
  Serial.begin(9600);
  pinMode(7, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(7), isr, FALLING);
}

void loop() {
  Serial.print('\r');
  Serial.print(n);
  delay(200);
}
