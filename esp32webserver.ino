#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <ESP32Servo.h>

#define DHTPIN 4         // Pin where the DHT22 sensor is connected
#define DHTTYPE DHT22    // DHT type (DHT11, DHT22, DHT21)

WebServer server(80);
DHT dht(DHTPIN, DHTTYPE);
Servo myservo;

// Replace with your network credentials
const char* ssid = "your_SSID";     
const char* password = "your_PASSWORD";    

int GREEN_LED_PIN = 12;
int RED_LED_PIN = 13;

String ledStateGreen = "OFF";
String ledStateRed = "OFF";
int servoAngle = 0; // Servo motor angle

void setup() {
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  Serial.begin(9600);
  connectToWifi();
  beginServer();
  myservo.attach(5); // Pin where the servo motor is connected
  dht.begin();
}

void loop() {
  server.handleClient();
}

void connectToWifi() {
  WiFi.enableSTA(true);
  delay(2000);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void beginServer() {
  server.on("/", handleRoot);
  server.on("/setservo", HTTP_POST, handleSetServo); // Endpoint to set the servo angle
  server.on("/controlled", handleControlled); // Endpoint to control the LEDs
  server.begin();
  Serial.println("HTTP server started");
}

void handleRoot() {
  String page = "<!DOCTYPE html><html lang=en-EN><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  page += "<title>ESP32 WebServer</title>";
  page += "<style> body { background-color: #f2f2f2; font-family: Arial, Helvetica, sans-serif; text-align: center; }</style>";
  page += "<style> .container { display: flex; flex-direction: column; align-items: center; justify-content: center; height: 100vh; }</style>";
  page += "<style> button { margin: 10px; padding: 10px 20px; border: none; border-radius: 5px; cursor: pointer; }</style>";
  page += "</head><body><div class='container'>";
  page += "<h1>ESP32 WebServer</h1>";
  page += "<h3>Green LED: " + ledStateGreen + "</h3>";
  page += "<form action='/controlled' method='POST'>";
  page += "<button name='green' value='1' style='background-color: #4CAF50; color: white;' >ON</button>";
  page += "<button name='green' value='0' style='background-color: #f44336; color: white;' >OFF</button>";
  page += "</form>";
  page += "<h3>Red LED: " + ledStateRed + "</h3>";
  page += "<form action='/controlled' method='POST'>";
  page += "<button name='red' value='1' style='background-color: #4CAF50; color: white;' >ON</button>";
  page += "<button name='red' value='0' style='background-color: #f44336; color: white;' >OFF</button>";
  page += "</form>";
  page += "<h3>Temperature: " + String(dht.readTemperature()) + " °C</h3>";
  page += "<h3>Humidity: " + String(dht.readHumidity()) + " %</h3>";
  page += "<h3>Servo Motor Angle: " + String(servoAngle) + " °</h3>";
  page += "<form action='/setservo' method='POST'>";
  page += "<button name='servo' value='100'>OPEN</button>";
  page += "<button name='servo' value='0'>CLOSE</button>";
  page += "</form>";
  page += "</div></body></html>";
  server.send(200, "text/html", page);
}

void handleControlled() {
  if (server.hasArg("green")) {
    String greenValue = server.arg("green");
    if (greenValue == "1") {
      digitalWrite(GREEN_LED_PIN, HIGH);
      ledStateGreen = "ON";
    } else {
      digitalWrite(GREEN_LED_PIN, LOW);
      ledStateGreen = "OFF";
    }
  }

  if (server.hasArg("red")) {
    String redValue = server.arg("red");
    if (redValue == "1") {
      digitalWrite(RED_LED_PIN, HIGH);
      ledStateRed = "ON";
    } else {
      digitalWrite(RED_LED_PIN, LOW);
      ledStateRed = "OFF";
    }
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleSetServo() {
  if (server.hasArg("servo")) {
    String servoValue = server.arg("servo");
    servoAngle = servoValue.toInt();
    myservo.write(servoAngle);
  }
  server.sendHeader("Location", "/");
  server.send(303);
}
