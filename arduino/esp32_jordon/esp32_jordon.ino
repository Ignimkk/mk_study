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
  <div>
  Photoresistor Value : <div id="sensor">None</div>
  </div>
  <br>
  <form action="/get">
  Servo Degree : <input type="text" name="degree" >
  <input type="submit" value="Submit" >
  </form>
  </center>
  <script>
    setInterval(getSensorValue, 100);
    function getSensorValue() {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("sensor").innerHTML = this.responseText;

        }
      };
      xhttp.open("GET", "/sensor", true);
      xhttp.send();
    }
  </script>
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

  server.on("/sensor", HTTP_GET, [] (AsyncWebServerRequest *request) {
    int sensor = analogRead(34);
    String s1 = String(sensor);
    Serial.println(s1);
    request->send(200, "text/plain", s1);
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

}
