volatile boolean state = false;

ISR (TIMER1_OVF_vect) {
  state = !state;
  digitalWrite(LED_BUILTIN, state);
}

void setup() {
  // set divider bits of Timer1 to PCK/4096, which is 2Hz at the 8MHz clock rate
  // http://www.atmel.com/Images/Atmel-2586-AVR-8-bit-Microcontroller-ATtiny25-ATtiny45-ATtiny85_Datasheet.pdf#page=90
  TCCR1 |= _BV(CS13) | _BV(CS12);
  // enable Timer/Counter1 Overflow Interrupt
  TIMSK |= _BV(TOIE1);
}

void loop() {
  ;
}
