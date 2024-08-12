#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;

int servo1_angle = 50;
int servo2_angle = 80;
int servo3_angle = 50;
int servo1_angle_pre = 0;
int servo2_angle_pre = 0;
int servo3_angle_pre = 0;
int input;
int selected_case = 0;
int servo_input;

void setup() {
  Serial.begin(9600);

  servo1.attach(8);
  servo2.attach(9);
  servo3.attach(10);
}

void loop() {
  static int selected_case = 0;
  static int servo_input = 0;
  static bool second_input_received = false;
  if (!second_input_received && Serial.available() > 0) {
    if (selected_case == 0) {
      selected_case = Serial.parseInt(); // 첫 번째 입력을 받음
      delay(1000);
      if (selected_case >= 1 && selected_case <= 3) {
        Serial.println("두 번째 입력을 기다리는 중...");
      } else {
        Serial.println("잘못된 케이스입니다. 1부터 3까지 입력하세요.");
        selected_case = 0;
      }
    } else {
      servo_input = Serial.parseInt(); // 두 번째 입력을 받음
      delay(1000);
      if (servo_input >= 0 && servo_input <= 180) {
        second_input_received = true; // 두 번째 입력이 받아졌음을 표시
        Serial.println("두 번째 입력을 받았습니다. 동작을 시작합니다.");
      } else {
        Serial.println("잘못된 입력입니다. 0부터 180까지의 값을 입력하세요.");
        selected_case = 0;
      }
    }
  }


  // If serial data is available
  // if (Serial.available() > 0) {
  //   // Read the incoming byte
  //   selected_case = Serial.parseInt();
  if (second_input_received)
  {
    
    // Based on the selected case, perform the corresponding action
    switch (selected_case)
    {
      case 1:
        
        // Read input for servo 1
        // servo_input = Serial.parseInt();
        servo1_angle = constrain(servo_input, 0, 180);
        servo1_angle_pre = servo1_angle;
        Serial.println("1번");
        if (servo1_angle > servo1_angle_pre) 
        {
          for (int i = servo1_angle_pre; i <= servo1_angle; i++)
          {
            input = i;
            delay(20);
            servo1.write(input);
            Serial.println(i);
            Serial.print("출발: ");
            Serial.println(servo1_angle);
            Serial.print("도착: ");
            Serial.println(servo1_angle_pre);
          }
        }
        else if (servo1_angle < servo1_angle_pre) 
        {
          for (int i = servo1_angle_pre; i >= servo1_angle; i--)
          {
            input = i;
            delay(20);
            servo1.write(input);
            Serial.print("출발: ");
            Serial.println(servo1_angle);
            Serial.print("도착: ");
            Serial.println(servo1_angle_pre);
          }
        }
        // servo1.write(servo1_angle);
        // println(servo1_angle);
        break;

      case 2:
        Serial.println("2번");
        // Read input for servo 2
        servo_input = Serial.parseInt();
        servo2_angle = constrain(servo_input, 70, 160);
        servo2_angle_pre = servo2_angle;
        if (servo2_angle > servo2_angle_pre) 
        {
          for (int i = servo2_angle_pre; i <= servo2_angle; i++)
          {
            input = i;
            delay(20);
            servo2.write(input);
            Serial.println(i);
            Serial.print("출발: ");
            Serial.println(servo2_angle);
            Serial.print("도착: ");
            Serial.println(servo2_angle_pre);
          }
        }
        else if (servo2_angle < servo2_angle_pre) 
        {
          for (int i = servo2_angle_pre; i >= servo2_angle; i--)
          {
            input = i;
            delay(20);
            servo2.write(input);
            Serial.print("출발: ");
            Serial.println(servo2_angle);
            Serial.print("도착: ");
            Serial.println(servo2_angle_pre);

          }
        }
        // servo2.write(servo2_angle);
        // println(servo2_angle);
        break;

      case 3:
        Serial.println("3번");
        // Read input for servo 3
        servo_input = Serial.parseInt();
        servo3_angle = constrain(servo_input, 60, 120);
        servo3_angle_pre = servo3_angle;
        // servo3.write(servo3_angle);
        // println(servo3_angle);
        if (servo3_angle > servo3_angle_pre) 
        {
          for (int i = servo3_angle_pre; i <= servo3_angle; i++)
          {
            input = i;
            delay(20);
            servo3.write(input);
            Serial.println(i);
            Serial.print("출발: ");
            Serial.println(servo3_angle);
            Serial.print("도착: ");
            Serial.println(servo3_angle_pre);
          }
        }
        else if (servo3_angle < servo3_angle_pre) 
        {
          for (int i = servo3_angle_pre; i >= servo3_angle; i--)
          {
            input = i;
            delay(20);
            servo3.write(input);
            Serial.print("출발: ");
            Serial.println(servo3_angle);
            Serial.print("도착: ");
            Serial.println(servo3_angle_pre);

          }
        }
        // servo2.write(servo2_angle);
        // println(servo2_angle);
        break;

      default:
        // If the selected case is not 1, 2, or 3, do nothing
        break;
    }
    selected_case = 0;
    second_input_received = false;

    // Clear the serial buffer
    // Serial.flush();
  }
}