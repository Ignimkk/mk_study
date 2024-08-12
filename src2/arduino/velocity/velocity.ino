
#include <Servo.h>


const int PUSH_BUTTON = 2;
bool flag;
Servo servo
int angle = 0;
int direction = 1;

void setup() {
  Serial.begin(9600);
  pinMode(PUSH_BUTTON, INPUT);
  flag = false;
  pinMode(9, OUTPUT);
  servo.attach(9)
}

void loop() {
  int button_status = digitalRead(PUSH_BUTTON);

  if (button_status == HIGH)
  {
    digitalWrite(9, HIGH);

    if (angle == 0)
    {
      direction = 1;
    }
    else if (angle == 180)
    {
      direction = -1;
    }
    for (angle = 0; angle < 180;)
    angle += (10 * direction);
    servo.write(angle);
    delay(20);

    if (angle == 180 || angle == 0) {
      flag = true;
    }
  }

  if (button_status == LOW && flag == true) {
    Serial.println("---");
    flag = false;
  }
}
