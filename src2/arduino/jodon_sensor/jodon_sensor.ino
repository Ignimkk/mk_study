const int LED = 9;


void setup()
{
// put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop()
{
// put your main code here, to run repeatedly:
  int light = analogRead(A0);
  int out = map(light, 50, 200,  5, 250);
  if (out < 5)
  {
    out = 5;
  }
  if (out > 250)
  {
    out = 250;
  }
  // Serial.print(light);
  // Serial.print(", ");
  // Serial.println(out);
  analogWrite(LED, out);

  int min = 0;
  int max = 0;

  int min0 = analogRead(A0);
  int max0;
  for (int i=0; i<1000; ++i)
  {
    int val = analogRead(A0);
    min0 = min(min0,val);
    max0 = max(max0, val);

  }
  Serial.print(min0);
  Serial.print(":");
  Serial.println(max0);


}