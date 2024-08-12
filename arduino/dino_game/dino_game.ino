#include <Servo.h>

const int PUSH_BUTTON = 2;
bool flag;

int pos = 20;
Servo servo;
int direction = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  flag = false;
  pinMode(9, OUTPUT);
  servo.attach(9);

}

void loop() {
  // put your main code here, to run repeatedly:
  int light = analogRead(A0);
  Serial.println(light);

  if (light < 840)
  {
    pos =

  }
}
