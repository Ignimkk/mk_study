
const int PUSH_BUTTON = 2;
bool flag;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PUSH_BUTTON, INPUT);
  flag = false;
}

void loop()
{
  int button_status = digitalRead(PUSH_BUTTON);
  
  if (button_status == HIGH)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    if (flag == false)
    {
      Serial.println(" push ");
      flag = true;
    }
  }

  if (button_status == LOW)
  {
    digitalWrite(LED_BUILTIN, LOW);
    if (flag == true)
    {
      Serial.println("---");
      flag = false;
    }
  }
}