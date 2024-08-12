#include <Servo.h>

const int PUSH_BUTTON = 2;
bool flag;

int pos = 0;
Servo servo;
int direction = 1;

void setup() {
  Serial.begin(9600);
  pinMode(PUSH_BUTTON, INPUT);
  flag = false;
  pinMode(9, OUTPUT);

  servo.attach(9);
}

void loop() {
  int button_status = digitalRead(PUSH_BUTTON);

  if (button_status == HIGH) {
    digitalWrite(9, HIGH);
    if (pos == 0) {
      direction = 1;
    } else if (pos == 180) {
      direction = -1;
    }

    pos += (10 * direction);
    servo.write(pos);
    delay(100);

    if (pos == 180 || pos == 0) {
      flag = true;
    }
  }

  if (button_status == LOW && flag == true) {
    Serial.println("---");
    flag = false;
  }
  if (pos > 180)
  {
    pos = 180;
  }

  if (pos < 0)
  {
    pos = 0;
  }
}