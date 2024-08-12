#include <SPI.h>
#include <MFRC522.h>
#include <List.hpp>
const int LED_B = 2;
const int LED_G = 3;
const int LED_R = 4;
const int BUTTON_PIN = 7;
const int RST_PIN = 9;
const int SS_PIN = 10;
int count = 0;

typedef enum
{
  REGISTRATION = 0,
  VERIFICATION
} RFID_STATUS;

MFRC522 rc522(SS_PIN, RST_PIN);
RFID_STATUS rfid_status;
List<MFRC522::Uid> tag_list;

int buttonPress() {
  int press;
  int buttonState;
  static int prevButtonState = LOW;
  buttonState = digitalRead(BUTTON_PIN);
  press = (buttonState == HIGH && prevButtonState == LOW);
  prevButtonState = buttonState;
  return press;
}

void printUID(MFRC522::Uid uid)
{
  for (byte i = 0; i < 4; i++)
  {
    Serial.print(uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(uid.uidByte[i], HEX);
  }
  Serial.println();
}

bool checkUID(MFRC522::Uid uid)
{
  for (int i = 0; i < tag_list.getSize(); i++)
  {
    if (memcmp(tag_list.get(i).uidByte, rc522.uid.uidByte, 4) == 0)
    {
      return true;
    }
  }
  return false;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  SPI.begin();
  rc522.PCD_Init();
  rfid_status = RFID_STATUS::REGISTRATION;
  Serial.println("[STATUS] Registration");
}

void loop() {
  if (buttonPress() == true)
  {
    if (rfid_status == RFID_STATUS::REGISTRATION)
    {
      rfid_status = RFID_STATUS::VERIFICATION;
      Serial.println("[STATUS] Verification");
    }
    else
    {
      rfid_status = RFID_STATUS::REGISTRATION;
      Serial.println("[STATUS] Registration");
    }
  }
  if (!rc522.PICC_IsNewCardPresent()) {
    return;
  }
  if (!rc522.PICC_ReadCardSerial()) {
    return;
  }
  if (rfid_status == RFID_STATUS::REGISTRATION)
  {
    if (checkUID(rc522.uid) == false)
    {
      tag_list.addLast(rc522.uid);
      Serial.print("Registration Tag : ");
      tag_list.addLast(rc522.uid);
      printUID(rc522.uid);
    }
  }
  else // rfid_status == VERIFICATION
  {
    Serial.print("Verification Tag : ");
    if (checkUID(rc522.uid) == true)
    {

      Serial.println("Valid");
      for (count = 0; count < 3; count++)
      {
        digitalWrite(LED_G, LOW);
        digitalWrite(LED_B, HIGH);
        delay(500);
        digitalWrite(LED_B, LOW);
        delay(500);
        digitalWrite(LED_G, HIGH);
      }
      count = 0;
    }
    else
    {
      Serial.println("Invalid");
      for (count = 0; count < 3; count++)
      {
        digitalWrite(LED_G, LOW);
        digitalWrite(LED_R, HIGH);
        delay(500);
        digitalWrite(LED_R, LOW);
        delay(500);
        digitalWrite(LED_G, HIGH);
      }
      count = 0;
    }
  }
  delay(100);
} 