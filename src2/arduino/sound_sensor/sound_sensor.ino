const int SOUND_SENSOR = A0;
const int LED1 = 2;
const int LED2 = 3;
const int LED3 = 4;
const int LED4= 5;
const int LED5= 6;
const int LED6 = 8;
const int LED7 = 9;
const int LED8 = 10;


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
  // level = level * 2;
  // if (level > 300)
  // {
  //   level = 255;
  // }
  // else if (level < 130)
  // {
  //   level = 0;
  // }
  // Serial.println(level);
  // Serial.println(level);

  int value = map(level, 57,957 ,0,255);
  
  Serial.println(value);
  
  if (value < 20)
  {
    value = 255;
  }
  


  if (value > 30 )
  {
    analogWrite(LED1,value);
    delay(100);
  }
  else
  {
    analogWrite(LED1,255);
  }
  
  if (value > 60 )
  {
    analogWrite(LED2,value);
    delay(100);
  }
  else
  {
    analogWrite(LED2,255);
  }

  if (value > 90 )
  {
    analogWrite(LED3,value);
    delay(100);
  }
  else
  {
    analogWrite(LED3,255);
  }

  if (value > 120 )
  {
    analogWrite(LED4,value);
    delay(100);
  }
  else
  {
    analogWrite(LED5,255);
  }
  if (value > 150 )
  {
    analogWrite(LED5,value);
    delay(100);
  }
  else
  {
    analogWrite(LED5,255);
  }
  if (value > 180 )
  {
    analogWrite(LED6,value);
    delay(100);
  }
  else
  {
    analogWrite(LED6,255);
  }
  if (value > 210 )
  {
    analogWrite(LED7,value);
    delay(100);
  }
  else
  {
    analogWrite(LED7,255);
  }
  if (value > 240 )
  {
    analogWrite(LED8,value);
    delay(100);
  }
  else
  {
    analogWrite(LED8,255);
  }



  // analogWrite(LED1,level);
  
  // analogWrite(LED2,level);

  // int min = 0;
  // int max = 0;

  // int min0 = analogRead(SOUND_SENSOR);
  // int max0;
  // for (int i=0; i<100; ++i)
  // {
  //   int val = analogRead(SOUND_SENSOR);
  //   min0 = min(min0,val);
  //   max0 = max(max0, val);
  // }
  // Serial.print(min0);
  // Serial.print(":");
  // Serial.println(max0);
  

}
