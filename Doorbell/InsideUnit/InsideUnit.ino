#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi Credentials
const char* ssid = "";
const char* password = "";

// Web Server on port 80
WebServer server(80);

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

// HTTP POST Handler
void handleLED() {
  if (server.method() == HTTP_POST) {
    String body = server.arg("plain");
    Serial.print("Received POST body: ");
    Serial.println(body);

    if (body == "on") {
      digitalWrite(ledPin, HIGH);
      shortTap();                  // Trigger DFPlayer when LED activates
      delay(1000);
      digitalWrite(ledPin, LOW);
    }
  }
  server.send(200, "text/plain", "OK");
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

  server.on("/led", HTTP_POST, handleLED);
  server.begin();
}

void loop() {
  server.handleClient();

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
