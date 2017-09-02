volatile boolean state = false;

ISR (TIMER1_OVF_vect) {
  TIMSK &= ~_BV(TOIE1);
  sei();
  state = !state;
  digitalWrite(LED_BUILTIN, state);
  TIMSK |= _BV(TOIE1);
}

void setup() {
  // Timer1 set to CK/1024  ~10 (8) hZ at 8 MHz clock rate,
  // for other CPU speeds select correct divider bits per data sheet
  // http://www.atmel.com/Images/Atmel-2586-AVR-8-bit-Microcontroller-ATtiny25-ATtiny45-ATtiny85_Datasheet.pdf#page=89
  // 8hZ: 13, 11, 10
  // 4hZ: 13, 12
  // 2hZ: 13, 12, 10
  // 1hZ: 13, 12, 11
  //.5hZ: 13, 12, 11, 10
  TCCR1 |= _BV(CS12) | _BV(CS13);// | _BV(CS11) | _BV(CS10);
  //TCCR1 &= ~_BV(CS10);
  TIMSK |= _BV(TOIE1);  // Enable Timer/Counter1 Overflow Interrupt

  sei(); // enable interrupts
}

void loop() {
  ;
}
