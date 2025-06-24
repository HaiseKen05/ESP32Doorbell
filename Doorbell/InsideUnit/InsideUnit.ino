#include <WiFi.h>
#include <WiFiUdp.h>

// Wi-Fi Credentials
const char* ssid = ""; // Input your WiFi network here
const char* password = ""; // WiFi Password

// UDP Settings
WiFiUDP udp;
const int udpPort = 4210;
char incomingPacket[255];

// Pins
const int ledPin = 2;              // Main output LED
const int wifiStatusLed = 4;       // Wi-Fi status indicator
#define DF_IO_PIN 18               // DFPlayer IO trigger

// Timing Configs
const uint32_t TAP_MS = 150;
unsigned long lastReconnectAttempt = 0;

// Simulate a short tap on DFPlayer
void shortTap() {
  pinMode(DF_IO_PIN, OUTPUT);
  digitalWrite(DF_IO_PIN, LOW);
  delay(TAP_MS);
  pinMode(DF_IO_PIN, INPUT_PULLUP);  // Return to idle state
}

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(wifiStatusLed, OUTPUT);
  pinMode(DF_IO_PIN, INPUT_PULLUP);  // DFPlayer pin starts idle

  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  digitalWrite(wifiStatusLed, HIGH); // Indicate Wi-Fi is ready

  // Begin UDP listener
  udp.begin(udpPort);
  Serial.println("UDP server started");
}

void loop() {
  // Check for incoming UDP packets
  int packetSize = udp.parsePacket();
  if (packetSize) {
    int len = udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = 0;  // Null-terminate the string
    }

    Serial.print("Received UDP packet: ");
    Serial.println(incomingPacket);

    if (String(incomingPacket) == "on") {
      digitalWrite(ledPin, HIGH);
      shortTap();                  // Trigger DFPlayer when LED activates
      delay(1000);
      digitalWrite(ledPin, LOW);
    }
  }

  // Wi-Fi Reconnect Logic
  if (WiFi.status() != WL_CONNECTED && millis() - lastReconnectAttempt > 30000) {
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.begin(ssid, password);
    lastReconnectAttempt = millis();
  }

  // Wi-Fi LED status
  digitalWrite(wifiStatusLed, WiFi.status() == WL_CONNECTED ? HIGH : LOW);
}
