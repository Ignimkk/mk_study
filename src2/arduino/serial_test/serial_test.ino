const int R_LED = 9;
void setup() {
  Serial.begin(9600); // 시리얼 통신 시작
  analogWrite(R_LED, 255);
}

void loop() {
  if (Serial.available() > 0) { 
    String input = Serial.readStringUntil('\n');  
    if (input == "1") { 
      analogWrite(R_LED, 0);
    }
  }
}
