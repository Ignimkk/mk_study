const int SOUND_SENSOR = A0;
const int LED1 = 2;
int LED2 = 3;
int LED3 = 4;
int LED4= 5;
int LED5= 6;
int LED6 = 8;
int LED7 = 9;
int LED8 = 10;

void setup()
{
  Serial.begin(9600);
  pinMode(SOUND_SENSOR, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED8, OUTPUT);
}


void loop()
{
  int level = analogRead(SOUND_SENSOR);
  level = level * 2;
  int value = map(level, 120,1000,0,255);
  
  delay(200);

  if (value < 20)
  {
    value = 0;
  }
  Serial.println(value);

 if (value > 30)
 {
  analogWrite(LED1, value);
  delay(20);

  if (value > 60)
  {
    analogWrite(LED2, value);
    delay(20);
    if (value > 90)
    {
      analogWrite(LED3, value);
      delay(20);

      if (value > 120)
      {
        analogWrite(LED4, value);
        delay(20);

        if (value > 150)
        {
          analogWrite(LED5, value);
          delay(20);

          if (value > 180)
          {
            analogWrite(LED6, value);
            delay(20);

            if (value > 210)
            {
              analogWrite(LED7, value);
              delay(20);

              if (value > 240)
              {
                analogWrite(LED8, value);
                delay(20);
              }
            }
          }
        }
      }
    }
  }
 }

  // if (value == 0)
  // {
  //   analogWrite(LED1 , 255);
  //   analogWrite(LED2 , 255);
  //   analogWrite(LED3 , 255);
  //   analogWrite(LED4 , 255);
  //   analogWrite(LED5 , 255);
  //   analogWrite(LED6 , 255);
    
  //   analogWrite(LED7 , 255);
  //   analogWrite(LED8 , 255);
  // }
}
