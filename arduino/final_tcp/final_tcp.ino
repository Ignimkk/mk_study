#include <WiFi.h>

const char *ssid = "addinedu_class_1(2.4G)";
const char *password = "addinedu1";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  
  // WiFi에 연결된 후 IP 주소를 출력
  Serial.print("ESP32 IP address: ");
  Serial.println(WiFi.localIP());
  
  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("Client connected");
    while (client.connected()) {
      while (client.available() > 0) {
        uint8_t data = client.read();
        Serial.write(data);  // 이 줄은 수신된 데이터를 시리얼 모니터에 출력
      }
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}
