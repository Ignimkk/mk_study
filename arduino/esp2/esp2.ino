#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>


const char *ssid = "addinedu_class_1(2.4G)";
const char *password = "addinedu1";
const int ledPin1 = 21;
const int ledPin2 = 22;
const int ledPin3 = 23;

AsyncWebServer server(80);

const char html[] PROGMEM = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <body>
  <center>
  <h1>Hello, ESP32 web server!</h1>
  <div>LED PIN 21 :
  <input type="checkbox" onchange="toggleCheckBox1(this)" />
  </div><br>
  <div>LED PIN 22 :
  <input type="checkbox" onchange="toggleCheckBox2(this)" />
  </div><br>
  <div>LED PIN 23 :
  <input type="checkbox" onchange="toggleCheckBox3(this)" />
  </div>
  <script>
  function toggleCheckBox1(element) {
    var req = new XMLHttpRequest();
    if (element.checked)
    {
      req.open("GET", "/on1", true);

    }
    else
    {
      req.open("GET", "/off1", true);
    }
    req.send();
  }
  function toggleCheckBox2(element) {
    var req = new XMLHttpRequest();
    if (element.checked)
    {
      req.open("GET", "/on2", true);

    }
    else
    {
      req.open("GET", "/off2", true);
    }
    req.send();
  }
  function toggleCheckBox3(element) {
    var req = new XMLHttpRequest();
    if (element.checked)
    {
      req.open("GET", "/on3", true);

    }
    else
    {
      req.open("GET", "/off3", true);
    }
    req.send();
  }
  </script>
  </center>
  </body>
  </html>

)rawliteral";

String processor(const String& var)
{
  Serial.println(var);
  return var;
}

void setup()
{
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  digitalWrite(ledPin1, LOW); 
  digitalWrite(ledPin2, LOW); 
  digitalWrite(ledPin3, LOW); 

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

  server.on("/", HTTP_GET, [] (AsyncWebServerRequest *req) {
    req->send_P(200, "text/html", html, processor);
  });
  server.on("/on1", HTTP_GET, [] (AsyncWebServerRequest *req) {
    digitalWrite(ledPin1, HIGH);
    req->send_P(200, "text/html", html, processor);
  });
  server.on("/off1", HTTP_GET, [] (AsyncWebServerRequest *req) {
    digitalWrite(ledPin1, LOW);
    req->send_P(200, "text/html", html, processor);
  });
  server.on("/on2", HTTP_GET, [] (AsyncWebServerRequest *req) {
    digitalWrite(ledPin2, HIGH);
    req->send_P(200, "text/html", html, processor);
  });
  server.on("/off2", HTTP_GET, [] (AsyncWebServerRequest *req) {
    digitalWrite(ledPin2, LOW);
    req->send_P(200, "text/html", html, processor);
  });
  server.on("/on3", HTTP_GET, [] (AsyncWebServerRequest *req) {
    digitalWrite(ledPin3, HIGH);
    req->send_P(200, "text/html", html, processor);
  });
  server.on("/off3", HTTP_GET, [] (AsyncWebServerRequest *req) {
    digitalWrite(ledPin3, LOW);
    req->send_P(200, "text/html", html, processor);
  });
  
  server.begin();

  Serial.println("HTTP Server Started!");
  delay(100);
}


void loop() {
  // put your main code here, to run repeatedly:

}
