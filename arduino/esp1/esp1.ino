#include <WiFi.h>
#include <WebServer.h>


const char *ssid = "addinedu308_2.4GHz";
const char *password = "addinedu1";
const int ledPin = 23;



WebServer server(80);
void handle_root();

const char html[] PROGMEM = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <body>
  <center>
  <h1>Hello, ESP32 web server!</h1>
  <a href="on"><button>LED ON</button></a>
  <a href="off"><button>LED OFF</button></a>
  </center>
  </body>
  </html>

)rawliteral";

void handle_root()
{
  server.send(200, "text/html", html);
}

void ledon()
{
  Serial.println("on");
  digitalWrite(ledPin, HIGH);
  server.send(200, "text/html", html);
}

void ledoff()
{
  Serial.println("off");
  digitalWrite(ledPin, LOW);
  server.send(200, "text/html", html);
}

void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  Serial.println("ESP32 Web Server Start");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");

  }
  Serial.println();

  Serial.print("IP address:");
  Serial.println(WiFi.localIP());

  server.on("/", handle_root);
  server.on("/on",HTTP_GET, ledon);
  server.on("/off", HTTP_GET, ledoff);
  server.begin();

  Serial.println("HTTP Server Started!");
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();

}
