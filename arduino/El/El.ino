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
bool move_flag;
int current_floor;
int NEXT_floor;
unsigned long time_start;
unsigned long move_duration = 500;
unsigned long move_start_time;
// const int LED_list[7] = {2,3,4,5,6,7,8};
bool button1_pressed = false;
bool button2_pressed = false;
bool button3_pressed = false;

int buttonPress_1() {
  int press;
  int buttonState;
  static int prevButtonState = LOW;
  buttonState = digitalRead(Button_1);
  press = (buttonState == HIGH && prevButtonState == LOW);
  prevButtonState = buttonState;
  if (press) {
    button1_pressed = true;
  }
  return press;
}

int buttonPress_2() {
  int press;
  int buttonState;
  static int prevButtonState = LOW;
  buttonState = digitalRead(Button_2);
  press = (buttonState == HIGH && prevButtonState == LOW);
  prevButtonState = buttonState;
  if (press) {
    button2_pressed = true;
  }
  return press;
}

int buttonPress_3() {
  int press;
  int buttonState;
  static int prevButtonState = LOW;
  buttonState = digitalRead(Button_3);
  press = (buttonState == HIGH && prevButtonState == LOW);
  prevButtonState = buttonState;
  if (press) {
    button3_pressed = true;
  }
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

void setDestination(int destination) {
  NEXT_floor = destination;
  move_start_time = millis();
  move_flag = true; 
}

void move_floor(int current_floor, int NEXT_floor) {
  unsigned long move_start_time = millis();
  unsigned char j = current_floor;
  bool reached_destination = false;
  
  while (!reached_destination) {
    unsigned long current_time = millis();
    if (current_time - move_start_time >= move_duration) {
      digitalWrite(j, LOW); 
      if (j < NEXT_floor) {
        j++; 
      } else if (j > NEXT_floor) {
        j--; 
      } else {
        reached_destination = true;
      }
      digitalWrite(j, HIGH); 
      move_start_time = current_time; 
    }
    
    
    if (digitalRead(Button_1) == HIGH) {
      NEXT_floor = 2;
    }
    if (digitalRead(Button_2) == HIGH) {
      NEXT_floor = 5;
    }
    if (digitalRead(Button_3) == HIGH) {
      NEXT_floor = 8;
    }
    if (reached_destination) {
      current_floor = j;
      reached_destination = false;
    }
    
  }

  digitalWrite(j, LOW); 
  
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
  move_flag = false;
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
    analogWrite(LED_G1, 0);
    move_flag = false;
  }

  if (buttonPress_2() == true)
  {
    analogWrite(LED_G2, 255);
    current_floor_LED();
    NEXT_floor = 5;
    move_floor(current_floor, NEXT_floor);
    analogWrite(LED_G2, 0);
    move_flag = false;
  }

  if (buttonPress_3() == true)
  {                    
    analogWrite(LED_G3, 255);
    current_floor_LED();
    NEXT_floor = 8;
    move_floor(current_floor, NEXT_floor);
    analogWrite(LED_G3, 0);
    move_flag = false;
  }

  if (move_flag) {
    move_floor(current_floor, NEXT_floor);
    move_flag = false; 
  }
  
  
}