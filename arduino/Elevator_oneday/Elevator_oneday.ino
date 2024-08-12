const int LED_R1 = 2;
const int LED_Y1 = 3;
const int LED_Y2 = 4;
const int LED_R2 = 5;
const int LED_Y3 = 6;
const int LED_Y4 = 7;
const int LED_R3 = 8;
const int LED_G1 = A0;
const int LED_G2 = 9;
const int LED_G3 = 10;
const int Button_1 = 11;
const int Button_2 = 12;
const int Button_3 = 13;
bool Button_flag;
int current_floor;
int NEXT_floor;
unsigned long time_start, time_current, time_previous;

// const int LED_list[7] = {LED_R1,LED_Y1,LED_Y2,LED_R2,LED_Y3,LED_Y4,LED_R3};

int buttonPress_1() {
  int press;
  int buttonState;
  int NEXT_floor = 2;
  static int prevButtonState = LOW;
  buttonState = digitalRead(Button_1);
  press = (buttonState == HIGH && prevButtonState == LOW);
  prevButtonState = buttonState;
  return press;
}

int buttonPress_2() {
  int press;
  int buttonState;
  int NEXT_floor = 5;
  static int prevButtonState = LOW;
  buttonState = digitalRead(Button_2);
  press = (buttonState == HIGH && prevButtonState == LOW);
  prevButtonState = buttonState;
  return press;
}

int buttonPress_3() {

  int press;
  int buttonState;
  int NEXT_floor = 8;
  static int prevButtonState = LOW;
  buttonState = digitalRead(Button_3);
  press = (buttonState == HIGH && prevButtonState == LOW);
  prevButtonState = buttonState;
  return press;
}

void current_floor_LED()
{
  if (digitalRead(LED_R1) == HIGH)
  {
    current_floor = 2;
    
  }
  else if (digitalRead(LED_R2) == HIGH)
  {
    current_floor = 5;
   
  }
  else if (digitalRead(LED_R3) == HIGH)
  {
    current_floor = 8;
  }
}

void move_floor(int current_floor, int NEXT_floor)
{
  unsigned char j;
  if (NEXT_floor > current_floor)
  {
    for(j = current_floor; j < NEXT_floor; j++)
    {
      digitalWrite(j, LOW);
      delay(300);
      digitalWrite(j+1, HIGH);
      delay(300);
    }
  }
  if (NEXT_floor < current_floor)
  {
    for (j = current_floor; j > NEXT_floor; j--)
    {
      digitalWrite(j, LOW);
      delay(300);
      digitalWrite(j-1, HIGH);
      delay(300);
    }
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(LED_R1, OUTPUT);
  pinMode(LED_Y1, OUTPUT);
  pinMode(LED_Y2, OUTPUT);
  pinMode(LED_R2, OUTPUT);
  pinMode(LED_Y3, OUTPUT);
  pinMode(LED_Y4, OUTPUT);
  pinMode(LED_R3, OUTPUT);
  pinMode(LED_G1, OUTPUT);
  pinMode(LED_G2, OUTPUT);
  pinMode(LED_G3, OUTPUT);
  pinMode(Button_1, INPUT);
  pinMode(Button_2, INPUT);
  pinMode(Button_3, INPUT);
  Button_flag = false;
  digitalWrite(LED_R1, HIGH);
  current_floor = 2;
  
}

void loop()
{
  if (buttonPress_1() == true)
  {
    analogWrite(LED_G1, 255);
    
    current_floor_LED();
    
    NEXT_floor = 2;
    move_floor(current_floor, NEXT_floor);

    digitalWrite(LED_R1, HIGH);
    analogWrite(LED_G1, 0);
  }

  if (buttonPress_2() == true)
  {
    analogWrite(LED_G2, 255);
    current_floor_LED();
    NEXT_floor = 5;
    move_floor(current_floor, NEXT_floor);
    digitalWrite(LED_R2, HIGH);
    analogWrite(LED_G2, 0);
  }

  if   (buttonPress_3() == true)
  {                    
    analogWrite(LED_G3, 255);
    current_floor_LED();
    NEXT_floor = 8;
    move_floor(current_floor, NEXT_floor);
    digitalWrite(LED_R3, HIGH);
    analogWrite(LED_G3, 0);
  }
}

