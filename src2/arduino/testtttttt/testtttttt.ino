#include <SoftwareSerial.h>
int a=0;
SoftwareSerial A_Serial(7,8);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  A_Serial.begin(9600);
}

void loop() {
  if (Serial.available()) { // 시리얼 모니터에서 입력을 받을 때
    char input = Serial.read(); // 입력을 읽음
    A_Serial.write(input); // 다른 보드로 입력을 전송
  }
}