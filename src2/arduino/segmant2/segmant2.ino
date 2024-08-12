int digits [10][7]{
  {0,0,0,0,0,0,1}, // digit 0
  {1,0,0,1,1,1,1}, // digit 1
  {0,0,1,0,0,1,0}, // digit 2
  {0,0,0,0,1,1,0}, // digit 3
  {1,0,0,1,1,0,0}, // digit 4
  {0,1,0,0,1,0,0}, // digit 5
  {0,1,0,0,0,0,0}, // digit 6
  {0,0,0,1,1,1,1}, // digit 7
  {0,0,0,0,0,0,0}, // digit 8
  {0,0,0,0,1,0,0} // digit 9
};
const int BUTTON_PIN = 13;
int clicks = 0;

void displayDigit(int d)
{
  if (digits[d][0]==1) digitalWrite(2, LOW); else digitalWrite(2, HIGH); //A
  if (digits[d][1]==1) digitalWrite(3, LOW); else digitalWrite(3, HIGH); //B
  if (digits[d][2]==1) digitalWrite(4, LOW); else digitalWrite(4, HIGH); //C
  if (digits[d][3]==1) digitalWrite(5, LOW); else digitalWrite(5, HIGH); //D
  if (digits[d][4]==1) digitalWrite(6, LOW); else digitalWrite(6, HIGH); //E
  if (digits[d][5]==1) digitalWrite(7, LOW); else digitalWrite(7, HIGH); //F
  if (digits[d][6]==1) digitalWrite(8, LOW); else digitalWrite(8, HIGH); //G
}

void setup()
{
  pinMode(2, OUTPUT);// Segment A
  pinMode(3, OUTPUT);// Segment B
  pinMode(4, OUTPUT);// Segment C
  pinMode(5, OUTPUT);// Segment D
  pinMode(6, OUTPUT);// Segment E
  pinMode(7, OUTPUT);// Segment F
  pinMode(8, OUTPUT);// Segment G
  pinMode(BUTTON_PIN, INPUT); //BUTTON
  Serial.begin(9600);
  displayDigit(clicks);
}

int buttonPress()
{
  int press;
  int buttonState;
  static int prevButtonState = LOW;
  buttonState = digitalRead(BUTTON_PIN);
  press = (buttonState == HIGH && prevButtonState == LOW);
  prevButtonState = buttonState;
  return press;
}


void loop()
{
  if (buttonPress())
  {
    displayDigit(0);
    delay(1000);
    displayDigit(1);
    delay(1000);
    displayDigit(0);
    delay(1000);
    displayDigit(2);
    delay(1000);
    displayDigit(6);
    delay(1000);
    displayDigit(8);
    delay(1000);
    displayDigit(7);
    delay(1000);
    displayDigit(1);
    delay(1000);
    displayDigit(5);
    delay(1000);
    displayDigit(4);
    delay(1000);
    displayDigit(0);
    delay(1000);


  }

}
