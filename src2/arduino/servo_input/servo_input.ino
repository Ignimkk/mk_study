#include <Servo.h>

Servo servo;
int tmp = 0, tmp_pre = 0;
int input;

void setup() {
  Serial.begin(9600);
  
  // 서보 모터에 전원을 제공하지 않습니다.
  delay(5000); // 서보 모터가 초기 위치로 이동하는 것을 방지하기 위한 딜레이
  
  // 서보 모터를 디지털 핀 9에 연결합니다.
  servo.attach(9); 
  // attach 함수 호출 후 서보 모터의 위치를 원하는 각도로 설정합니다.
  servo.write(0); // 서보 모터를 0도 위치로 이동
  delay(1000); // 강제로 이동한 후에 잠시 대기합니다.
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0) {
    String input_str = Serial.readStringUntil('\n');
    tmp_pre = tmp;
    tmp = input_str.toInt();
    if (tmp > 180) tmp = 180;
    else if (tmp < 0) tmp = 0;

    if (tmp > tmp_pre) {
      for (int i = tmp_pre; i <= tmp; i++) {
        input = i;
        delay(20);
        servo.write(input);
        Serial.print(" 입력 값 : ");
        Serial.print(input);
        Serial.print(" i값 : ");
        Serial.println(i);
      }
    }
    else if (tmp < tmp_pre) {
      for (int i = tmp_pre; i >= tmp; i--) {
        input = i;
        delay(20);
        servo.write(input);
        Serial.print(" 입력 값 : ");
        Serial.print(input);
        Serial.print(" i값 : ");
        Serial.println(i);
      }
    }
    else {
      // tmp와 tmp_pre가 같을 때의 처리 (변경사항이 없을 때)
    }
  }
}
