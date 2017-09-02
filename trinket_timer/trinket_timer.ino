#define F_CPU  8000000UL

volatile boolean state = false;

ISR (TIMER1_OVF_vect) {
  TIMSK &= ~_BV(TOIE1); // I have this thing about shutting off interrupts
  sei();                // ... but only the ones I'm servicing

  state = !state;
  digitalWrite(LED_BUILTIN, state);

  TIMSK |= _BV(TOIE1);
}

void setup() {
  // Timer1 set to CK/1024  ~10 (8) hZ at 8 MHz clock rate,
  // for other CPU speeds select correct divider bits per data sheet
  // http://www.atmel.com/Images/Atmel-2586-AVR-8-bit-Microcontroller-ATtiny25-ATtiny45-ATtiny85_Datasheet.pdf
  TCCR1 |= _BV(CS13) | _BV(CS11) | _BV(CS10);
  TIMSK |= _BV(TOIE1);  // Enable Timer/Counter1 Overflow Interrupt

  sei(); // enable interrupts
}

void loop() {
  ;
}
