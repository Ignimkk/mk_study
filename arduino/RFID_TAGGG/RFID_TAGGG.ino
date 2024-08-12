#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>  // for RTC
#include <DS3231.h>  // for RTC

#define RST_PIN         9
#define SS_PIN          10
#define RTC_PIN         A4  // RTC SDA
#define RTC_SQW_PIN     A5  // RTC SQW

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

DS3231 rtc(RTC_PIN, RTC_SQW_PIN);  // Create RTC instance

void setup() {
  Serial.begin(9600);  // Initialize serial communications
  SPI.begin();          // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522 card
  
  rtc.begin();  // Initialize RTC
}

void loop() {
  // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    Serial.println("New card detected!");

    // Prepare data to write
    String data = "사과,2,곽민기,A구역,보관위치," + getCurrentTime() + ",양호"; // Data to write
    byte dataBytes[data.length() + 1]; // Byte array for data
    data.getBytes(dataBytes, data.length() + 1);

    // Write data to the RFID tag
    if (mfrc522.MIFARE_Write(1, dataBytes, data.length() + 1)) {
      Serial.println("Data written successfully.");
    } else {
      Serial.println("Failed to write data.");
    }
  }

  delay(1000);
}

String getCurrentTime() {
  DateTime now = rtc.now();
  char currentTime[20];
  sprintf(currentTime, "%04d-%02d-%02d %02d:%02d:%02d", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
  return String(currentTime);
}