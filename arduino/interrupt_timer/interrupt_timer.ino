const int ledPinR = 6;
const int ledPinL = 44;
volatile int cnt = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinL, OUTPUT);

  // Timer: Control loop
  cli(); // Disable interrupts
  TCCR4A = 0; // set entire TCCR4A register to 0
  TCCR4B = 0; // set entire TCCR4B register to 0
  TCNT4 = 0; // initialize counter value to 0
  OCR4A = 15624; // (16*10^6) / (1*1024) - 1 (1 Hz, must be <65536)
  TCCR4B |= (1 << WGM12); // CTC mode
  TCCR4B |= (1 << CS12) | (1 << CS10); // 1024 prescaler
  TIMSK4 |= (1 << OCIE4A); // enable timer compare interrupt
  sei(); // Enable interrupts
}

void loop() {
  // put your main code here, to run repeatedly:
  // No need to put anything here for this example
}

ISR(TIMER4_COMPA_vect) {
  cnt++;
  Serial.print("Seconds passed: ");
  Serial.println(cnt);
  if (cnt >= 60) { // Toggle every 60 seconds
    cnt = 0;
    // Toggle LEDs
    digitalWrite(ledPinR, !digitalRead(ledPinR));
    digitalWrite(ledPinL, !digitalRead(ledPinL));
  }
}
