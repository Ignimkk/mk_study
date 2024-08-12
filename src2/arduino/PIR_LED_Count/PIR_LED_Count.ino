const int PIR = 2;
const int LED = 4;
bool flag;
int count = 0;
const int limit = 50;

void setup()
{
  Serial.begin(9600);
  pinMode(PIR, INPUT);
  pinMode(LED, OUTPUT);
  flag = false;
}


void loop()
{
  int tmp = digitalRead(PIR);
  Serial.println(tmp); 


  if (tmp == 1)
  {
    flag = true;
  }

 
  if (flag == true)
  {
    count ++;
    analogWrite(LED,255);
    delay(100);

    if (count == limit)
    {
      flag = false;
      count = 0;
      analogWrite(LED,0);
    }
    

  }

}
