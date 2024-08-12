const int PIR = 2;
const int LED = 4;
int tmp;
unsigned long time;
int ff;
int end_time;
// unsigned long time;
// extern volatile unsigned long timer0_millis;

void setup()
{
  Serial.begin(9600);
  pinMode(PIR, INPUT);
  pinMode(LED, OUTPUT);
}

void loop()
{
  int tmp = digitalRead(PIR);
  // Serial.println(tmp);

  time = millis();
  delay(100);
  
  if (tmp == 1)
  {
    analogWrite(LED, 255);
    end_time = time + 5000;
    

  }
  ff = end_time - time;
  Serial.println(ff);

  if (ff < 5000)
  {
    analogWrite(LED, 255);
    
  }
  
  else
  {
    analogWrite(LED,0);
    time = 0;
  }
    
  

 

}
  


  