#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Display setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Wi-Fi credentials
const char* ssid = "ESP32-AP";
const char* password = "ESP32-Connect";
const char* receiverIP = "192.168.254.118";

// Pins
const int buttonPin = 4;
const int wifiLedPin = 2;

// Timing
unsigned long lastWifiCheck = 0;
const unsigned long wifiCheckInterval = 30000;

// Logging helper function (Serial + OLED)
void logMessage(String msg) {
  Serial.println(msg);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.println(msg);
  display.display();
}

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(wifiLedPin, OUTPUT);
  digitalWrite(wifiLedPin, LOW);

  Serial.begin(115200);

  // OLED Init
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Initializing...");
  display.display();

  WiFi.begin(ssid, password);
  logMessage("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    display.print(".");
    display.display();
    Serial.print(".");
  }

  logMessage("Connected!\nIP: " + WiFi.localIP().toString());
  digitalWrite(wifiLedPin, HIGH);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    sendSignal();
    delay(500);
  }

  if (millis() - lastWifiCheck >= wifiCheckInterval) {
    lastWifiCheck = millis();
    if (WiFi.status() != WL_CONNECTED) {
      logMessage("WiFi lost, reconnecting...");
      WiFi.disconnect();
      WiFi.begin(ssid, password);
      digitalWrite(wifiLedPin, LOW);
    } else {
      digitalWrite(wifiLedPin, HIGH);
    }
  }
}

void sendSignal() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://" + String(receiverIP) + "/led");
    http.addHeader("Content-Type", "text/plain");
    int httpCode = http.POST("on");
    logMessage("POST response: " + String(httpCode));
    http.end();
  } else {
    logMessage("WiFi not connected. Skipping POST.");
  }
}
