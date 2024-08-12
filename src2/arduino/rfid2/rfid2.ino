#include <SPI.h>
#include <MFRC522.h>
#include <List.hpp>

#define RST_PIN 9          // Configurable, see typical pin layout above
#define SS_PIN 10         // Configurable, see typical pin layout above

const int BUTTON_PIN = 7;
int LED_B = 2;
int LED_G = 3;
int LED_R = 4;
const byte MY_TAG[4] = {0xD3, 0xB4, 0x00, 0xF8};
const int RST_PIN = 9;
const int SS_PIN = 10;
int count = 0;

List<MFRC522::Uid> tag_list;

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

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  pinMode(LED_B,OUTPUT);
  pinMode(LED_G,OUTPUT);
  pinMode(LED_R,OUTPUT);
  digitalWrite(LED_G, HIGH);
  pinMode(BUTTON_PIN, INPUT);

  SPI.begin();
  rc522.PCD_Init();
  rfid_status = RFID_STATUS::REGISTRATION;
  Serial.println("[STATUS] Registration");
}



void loop()
{
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    delay(500);
    return;
  }
  if (! mfrc522.PICC_ReadCardSerial())
  {
    delay(500);
    return;
  }
  // 버튼 작동
  if (buttonPress() == true)
  {
    Serial.print("Read UID Tag : ");
    for (byte i =0; i < mfrc522.uid.size; i++)
    {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    }

    Serial.print(", Check UID Tag : " );
    if (memcmp(mfrc522.uid.uidByte, MY_TAG, 4) == 0)
    {
      Serial.print("Valid");
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
      Serial.print("Invalid");

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
    Serial.println();
    delay(1000);
    
  }
  else
  {
    mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
    Serial.print("Read UID Tag : ");
    for (byte i =0; i < mfrc522.uid.size; i++)
    {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);

    }
    Serial.println();

    tag_list.addLast(mfrc522.uid);

    Serial.print("Registered Tag List (");
    Serial.print(tag_list.getSize());
    Serial.print(") : ");
    Serial.println();

    for (int i = 0; i < tag_list.getSize(); i++)
    {
      for (byte j = 0; j<4; j++)
      {

        Serial.print(tag_list.get(i).uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(tag_list.get(i).uidByte[i], HEX);

      }
      Serial.println();
    }
    delay(1000)

  }



  // Serial.print("Read UID Tag : ");
  // for (byte i =0; i < mfrc522.uid.size; i++)
  // {
  //   Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
  //   Serial.print(mfrc522.uid.uidByte[i], HEX);
  // }

  // Serial.print(", Check UID Tag : " );
  // if (memcmp(mfrc522.uid.uidByte, MY_TAG, 4) == 0)
  // {
  //   Serial.print("Valid");
  //   for (count = 0; count < 3; count++)
  //   {
  //     digitalWrite(LED_G, LOW);
  //     digitalWrite(LED_B, HIGH);
  //     delay(500);
  //     digitalWrite(LED_B, LOW);
  //     delay(500);
  //     digitalWrite(LED_G, HIGH);
  //   }
  //   count = 0;
  // }
  // else
  // {
  //   Serial.print("Valid");

  //   for (count = 0; count < 3; count++)
  //   {
  //     digitalWrite(LED_G, LOW);
  //     digitalWrite(LED_R, HIGH);
  //     delay(500);
  //     digitalWrite(LED_R, LOW);
  //     delay(500);
  //     digitalWrite(LED_G, HIGH);
  //   }
  //   count = 0;
  // }
  // Serial.println();
  // delay(1000);

}
