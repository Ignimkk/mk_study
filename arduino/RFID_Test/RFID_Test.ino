#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9
#define SS_PIN          10

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  Serial.begin(9600);  // 시리얼 통신 속도 설정
  SPI.begin();          // SPI 버스 초기화
  mfrc522.PCD_Init();   // MFRC522 카드 초기화
}

void loop() {
  // 새로운 카드가 감지되었는지 확인
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Serial.println("New card detected!");

    // RFID 태그의 UID 읽기
    String tagUID = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      // 각 바이트를 2자리의 16진수로 변환하여 UID 문자열에 추가
      if (mfrc522.uid.uidByte[i] < 0x10) {
        tagUID += "0"; // 한 자리 16진수의 경우 0을 추가하여 두 자리로 만듭니다.
      }
      tagUID += String(mfrc522.uid.uidByte[i], HEX);
    }

    // 시리얼로 데이터 전송
    Serial.println(tagUID);

    delay(1000); // 1초 대기
  }
}
