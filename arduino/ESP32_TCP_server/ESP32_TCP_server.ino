#include <WiFi.h>
#include <ESP32Servo.h>

const char *ssid = "addinedu_class_1(2.4G)";
const char *password = "addinedu1";

Servo servo;
const int servo_pin = 5;

WiFiServer server(80);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("ESP32 TCP Server Start");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  pinMode(21,OUTPUT);
  pinMode(22,OUTPUT);
  pinMode(23,OUTPUT);
  servo.attach(servo_pin);
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());

  server.begin();

}

struct protocol {
  int pin = 21;
  int status = 0;
};

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();
  if (client) {
    Serial.print("Client connected  : ");
    Serial.println(client.remoteIP());

    struct protocol p;
    while (client.connected()) {
      char data[8];

      while (client.available() > 0) {
        client.readBytes(data, 8);
        memcpy(&p, data, sizeof(p));

        if (p.pin == servo_pin)
        {
          servo.write(p.status);
        }
        else
        {
          digitalWrite(p.pin, p.status);

        }

        digitalWrite(p.pin, p.status);
        Serial.println(p.pin);
        Serial.println(p.status);

        // char c = client.read();
        client.write(data, 8);
      }

      delay(10);
    }

    client.stop();
    Serial.println("Client Disconnected");
  }

}
