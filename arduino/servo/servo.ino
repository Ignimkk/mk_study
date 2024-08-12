#include <Servo.h>


int pos=180;
Servo servo;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(9);
}

void loop()
{

  // put your main code here, to run repeatedly:
  

  int light = analogRead(A0);
  Serial.println(light);
    
  if (light < 710)
  {
  
    pos = 140;
    // Serial.println(up);
    delay(100);
    servo.write(pos);
    delay(100);
    // Serial.println(up);
    
  }
  delay(100);
  pos = 180;
  servo.write(pos);
  // else
  // {
  //   delay(50);
  //   pos = 180;
  //   servo.write(pos);
  // }
  
}

