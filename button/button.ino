volatile byte minutes = 0, hours = 0;

volatile unsigned long lastISR = 0;
volatile unsigned long delta;
volatile byte sequence = 0;

void isr() {
  delta = millis() - lastISR;
  lastISR = millis();
  if (delta < 100) return; // debounce

  /**/ if (delta > 5000) sequence = 0;
  else if (delta > 4000) sequence = 4;
  else if (delta > 3000) sequence = 3;
  else if (delta > 2000) sequence = 2;
  else if (delta > 1000) sequence = 1;

  switch (sequence) {
    case 1: minutes = (minutes+1)  % 60; break;
    case 2: minutes = (minutes+10) % 60; break;
    case 3: hours   = (hours+1)    % 24; break;
    case 4: hours   = (hours+6)    % 24; break;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(7, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(7), isr, FALLING);
}

void loop() {
  Serial.print('\r');
  if (hours < 10) Serial.print('0');
  Serial.print(hours);
  Serial.print(':');
  if (minutes < 10) Serial.print('0');
  Serial.print(minutes);
  delay(50);
}
