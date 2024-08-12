#include <WiFi.h>
#include <ESP32Servo.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

Servo servo;
const int servo_pin = 5;

const char *ssid = "addinedu_class_1(2.4G)";
const char *password = "addinedu1";
const char* INPUT_PARAM1 = "degree";

AsyncWebServer server(80);

const char html[] PROGMEM = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <body>
  <center>
  <h1>Hello, ESP32 web server!</h1>
  <form action="/get">
  Servo Degree : <input type="text" name="degree" >
  <input type="submit" value="Submit" >
  </form>

  </center>
  </body>
  </html>

)rawliteral";

String processor(const String& var)
{
  Serial.println(var);
  return var;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("ESP32 Web Server Start");
  Serial.println(ssid);
  servo.attach(servo_pin);
  WiFi.begin(ssid, password);  

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");

  }
  Serial.println();

  Serial.print("IP address:");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [] (AsyncWebServerRequest *req) {
    req->send_P(200, "text/html", html, processor);
  });

  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *req) {
    String inputMessage = req->getParam(INPUT_PARAM1)->value();
    Serial.println(inputMessage);
    float degree = inputMessage.toFloat();
    servo.write(degree);
    req->send_P(200, "text/html", html, processor);
  });

  server.begin();
  Serial.println("HTTP Server Started!");
  delay(100);

}

void loop() {
  // // put your main code here, to run repeatedly:
  // while (Serial.available() > 0) {
  //   String input = Serial.readStringUntil('\n');
  //   float degree = input.toFloat();
  //   Serial.println(degree);
  //   servo.write(degree);
  // }

}
