#include <WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Display setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Wi-Fi credentials
const char* ssid = " "; // WiFi Name
const char* password = " "; // WiFi Password
const char* receiverIP = " ";  // e.g., "192.168.4.3" if using static IP setup

// UDP setup
WiFiUDP udp;
const int udpPort = 4210;

// Pins
const int buttonPin = 4; // You can change this to your desired GPIO Pin
const int wifiLedPin = 2; // Can use the Built-in LED or change to a different GPIO Pin 

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

  // Wi-Fi Init
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

  // Start UDP
  udp.begin(udpPort);  // Optional for sender but can help for receiving replies
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    sendSignal();
    delay(500);  // Debounce delay
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
    const char* message = "on";
    udp.beginPacket(receiverIP, udpPort);
    udp.write((const uint8_t*)message, strlen(message));  // Fixed line
    udp.endPacket();
    logMessage("Sent UDP: on");
  } else {
    logMessage("WiFi not connected. Skipping UDP.");
  }
}

