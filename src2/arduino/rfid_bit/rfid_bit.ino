#include <SPI.h>
#include <MFRC522.h>
 

const int RST_PIN = 9;
const int SS_PIN = 10;
MFRC522 rc522(SS_PIN, RST_PIN); 

struct TagData
{
  char name[16];
  long total;
  long payment;
};

MFRC522::StatusCode writeTagData(int index, MFRC522::MIFARE_Key key, TagData data)
{
  MFRC522::StatusCode status = checkAuth(index, key);
  if (status != MFRC522::STATUS_OK)
  {
    return status;
  }

  byte buffer[32];
  memset(buffer, 0x00, sizeof(buffer));
  memcpy(buffer, &data, sizeof(data));
  for (int i = 0; i<2; i++)
  {
    status = rc522.MIFARE_Write(index, buffer, sizeof(buffer));
    if (status != MFRC522::STATUS_OK)
    {
      Serial.print("Write Failed : ");
      Serial.println(rc522.GetStatusCodeName(status));
    }
  }
  return status;
}


int toInteger(byte* buffer, int offset = 0)
{
  return (buffer[offset + 1] << 8 | buffer[offset]);
}

MFRC522::StatusCode readInteger(int index, MFRC522::MIFARE_Key key, int& data)
{
  MFRC522::StatusCode status = checkAuth(index, key);
  if (status != MFRC522::STATUS_OK)
  {
    return status;
  }

  byte buffer[18];
  byte length = 18;

  status = rc522.MIFARE_Read(index, buffer, &length);
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("Read Failed : ");
    Serial.println(rc522.GetStatusCodeName(status));
  }
  else
  {
    data = toInteger(buffer);
  }
  return status;
}

void toBytes(byte* buffer, int data, int offset = 0)
{
  buffer[offset] = data & 0xFF;
  buffer[offset + 1] = (data >> 8) & 0xFF;
}

MFRC522::StatusCode writeInteger(int index, MFRC522::MIFARE_Key key, int data)
{
  MFRC522::StatusCode status = checkAuth(index, key);
  if (status != MFRC522::STATUS_OK)
  {
    return status;
  }

  byte buffer[16];
  memset(buffer, 0x00, sizeof(buffer));
  toBytes(buffer, data);

  status = rc522.MIFARE_Write(index, buffer, sizeof(buffer));
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("Write Failed : ");
    Serial.println(rc522.GetStatusCodeName(status));
  }

  return status;
}


MFRC522::StatusCode checkAuth(int index, MFRC522::MIFARE_Key key)
{
  MFRC522::StatusCode status = 
    rc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, index, &key, &(rc522.uid));
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("Authentication Failed:");
    Serial.println(rc522.GetStatusCodeName(status));
  }
  return status;
}

MFRC522::StatusCode writeString(int index, MFRC522::MIFARE_Key key, String data)
{
  MFRC522::StatusCode status = checkAuth(index, key);
  if (status != MFRC522::STATUS_OK)
  {
    return status;
  }
  char buffer[16];
  memset(buffer, 0x00, sizeof(buffer));
  data.toCharArray(buffer, data.length() + 1);

  status = rc522.MIFARE_Write(index, (byte*)&data, 16);

  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("Write Failed: ");
    Serial.println(rc522.GetStatusCodeName(status));
  }
  return status;
}

String cmd = "";

MFRC522::StatusCode readString(int index, MFRC522::MIFARE_Key key, String& data)
{
  MFRC522::StatusCode status = checkAuth(index, key);
  if (status != MFRC522::STATUS_OK)
  {
    return status;
  }

  byte buffer[18];
  byte length = 18;

  status = rc522.MIFARE_Read(index, buffer, &length);
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("Read Failed : ");
    Serial.println(rc522.GetStatusCodeName(status));
  }
  else
  {
    data = String((char*)buffer);
  }

  return status;
}



void setup()
{
  Serial.begin(9600);
  SPI.begin();	
  rc522.PCD_Init();	
  Serial.println("start!!");
}

void loop()
{

  while (Serial.available() > 0)
  {
    cmd = Serial.readStringUntil('\n');
  }

  if (!rc522.PICC_IsNewCardPresent())
  {
		return;
	}

	if (!rc522.PICC_ReadCardSerial())
  {
		return;
	}

  MFRC522::MIFARE_Key key;
  for (int i = 0; i < 6; i++)
  {
    key.keyByte[i] = 0xFF;
  }

  

  MFRC522::StatusCode status;
  TagData t_data;
  String s_temp;

  if (cmd.length() > 0)
  {
    Serial.print("cmd: ");
    switch(cmd.charAt(0))
    {
      case 'w':
        Serial.print("write");
        switch (cmd.charAt(1))
        {
          case 's':
            Serial.println("string");
            status = writeString(60, key, "sexymingi");
            rc522.PICC_DumpToSerial(&(rc522.uid));
            break;
          case 'i':
            Serial.println("integer");
            status = writeInteger(61, key, 32767);
            rc522.PICC_DumpToSerial(&(rc522.uid));
            break;
          case 't':
            Serial.println("struct");
            s_temp = "sexymingi";
            s_temp.toCharArray(t_data.name, s_temp.length() + 1);
            t_data.total = 2147483647;
            t_data.payment = 2000000000;
            status = writeTagData(56, key, t_data);
            rc522.PICC_DumpToSerial(&(rc522.uid));
            break;
          default:
            Serial.println("unknown");
            status = MFRC522::STATUS_ERROR;
            break;
        }
        break;
    }

  // MFRC522::StatusCode status;
  // String s_data;
  // int i_data;

  // if (cmd.length() > 0)
  // {
  //   Serial.print("cmd: ");
  //   switch(cmd.charAt(0))
  //   {
  //     case 'r':
  //       Serial.print("read");
  //       switch (cmd.charAt(1))
  //       {
  //         case 's':
  //           Serial.println(" string");
  //           status = writeString(60, key, s_data);
  //           Serial.println(s_data);
  //           rc522.PICC_DumpToSerial(&(rc522.uid));
  //           break;
  //         case 'i':
  //           Serial.println(" integer");
  //           status = writeInteger(61, key, i_data);
  //           Serial.println(i_data);
  //           rc522.PICC_DumpToSerial(&(rc522.uid));
  //           break;
  //         default:
  //           Serial.println("unknown");
  //           status = MFRC522::STATUS_ERROR;
  //           break;
  //       }
  //       break;
  //   }

    if (status == MFRC522::STATUS_OK)
    {
      Serial.println("succecss");
    }
  }

  // if (cmd.length() > 0 && cmd == "w")
  // {
  //   Serial.print("cmd: ");
  //   Serial.println(cmd);
  // }
  // else
  // {
  //   return;
  // }

  // const int index = 60;
  // MFRC522::StatusCode status;

  // MFRC522::MIFARE_Key key;
  // for (int i = 0; i < 6; i++)
  // {
  //   key.keyByte[i] = 0xFF;
  // }

  // --함수1--
  // status = rc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, index, &key, &(rc522.uid));
  // if (status != MFRC522::STATUS_OK)
  // {
  //   Serial.print("Authentication Failed:");
  //   Serial.println(rc522.GetStatusCodeName(status));

  //   return;
  // }

// --함수2--
  // char data[16];
  // memset(data, 0x00, sizeof(data));

  // String name = "mingi";
  // name.toCharArray(data, name.length() + 1);

  // status = rc522.MIFARE_Write(index, (byte*)&data, 16);
  // if (status != MFRC522::STATUS_OK)
  // {
  //   Serial.print("Write Failed: ");
  //   Serial.println(rc522.GetStatusCodeName(status));

  //   return;
  // }

  rc522.PICC_DumpToSerial(&(rc522.uid));
  delay(100);


}
