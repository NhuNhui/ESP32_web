#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "index.h"
#include "temparature.h"
#include "led.h"
#include "error_404.h"
#include "error_405.h"
#include <Adafruit_NeoPixel.h>
#include "LiquidCrystal_I2C.h"
#include "DHT20.h"
#include <Arduino.h>


Adafruit_NeoPixel pixels3(4, D5, NEO_GRB + NEO_KHZ800);
DHT20 dht20;
LiquidCrystal_I2C lcd(0x21,16,2); // địa chỉ màn hình là 0x21 hexa


const char *ssid = "10h37";     // CHANGE IT
const char *password = "12345678";  // CHANGE IT

AsyncWebServer server(80);

int LED_state = LOW;

int getTemp() {
  dht20.read();
  float temp = dht20.getTemperature();
  return int(temp);
}

int getHumi() {
  dht20.read();
  float humi = dht20.getHumidity();
  return int(humi);
}

int getLight() {
  int light_value = analogRead(A1);
  return light_value;
}

void onLed() {
  pixels3.setPixelColor(0, pixels3.Color(255,0,0));
  pixels3.setPixelColor(1, pixels3.Color(255,0,0)); 
  pixels3.setPixelColor(2, pixels3.Color(255,0,0)); 
  pixels3.setPixelColor(3, pixels3.Color(255,0,0));       
  pixels3.show();
}

void offLed() {
  pixels3.setPixelColor(0, pixels3.Color(0,0,0));
  pixels3.setPixelColor(1, pixels3.Color(0,0,0)); 
  pixels3.setPixelColor(2, pixels3.Color(0,0,0)); 
  pixels3.setPixelColor(3, pixels3.Color(0,0,0));       
  pixels3.show();
}

void setup() {
  Serial.begin(9600);
  pinMode(D13,OUTPUT);
  pixels3.begin();
  dht20.begin();
  //Initialize the LCD
  lcd.init();
  // Turn on the blacklight
  lcd.backlight();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Print the ESP32's IP address
  Serial.print("ESP32 Web Server's IP address: ");
  Serial.println(WiFi.localIP());

  
  // Serve the specified HTML pages
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("Web Server: home page");
        if (request->hasArg("state")) {
      String state = request->arg("state");
      if (state == "on") {
        LED_state = HIGH;
      } else if (state == "off") {
        LED_state = LOW;
      }

      // control LED here
      if (LED_state) {
        // Serial.println("ON LED");
        digitalWrite(D13, HIGH);
        onLed();
      }
      else {
        // Serial.println("OFF LED");
        digitalWrite(D13, LOW);
        offLed();
      }
      Serial.print(" => turning LED to ");
      Serial.println(state);
    }
    String html = HTML_CONTENT_HOME;  // Use the HTML content from the index.h file
    String temp = String(getTemp());
    String humi = String(getHumi());
    String light = String(getLight());
    html.replace("%temp_style%","--value:" + temp);
    html.replace("%humi_style%","--value:" + humi);
    html.replace("%light_style%", "--value:" + light);
    html.replace("%temp%",temp);
    html.replace("%humi%",humi);
    html.replace("%light%",light);
    Serial.println(temp + ", " + humi + ", " + light);
    request->send(200, "text/html", html);
  });

  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    String temp = String(getTemp());
    request->send(200, "text/plain", temp);
  });

  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    String humi = String(getHumi());
    request->send(200, "text/plain", humi);
  });

  server.on("/light", HTTP_GET, [](AsyncWebServerRequest *request){
    String light = String(getLight());
    request->send(200, "text/plain", light);
  });

  server.begin();
  Serial.println("ESP32 Web server started");

}

void loop() {
  // Your code can go here or be empty; the server is handled asynchronously
  dht20.read();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(dht20.getTemperature());
  lcd.setCursor(0, 1);
  lcd.print(dht20.getHumidity());
  delay(2000);
}
