#include <WiFi.h>
#include <HTTPClient.h>

// Fill these locally before uploading to ESP32.
// Do not commit real Wi-Fi or Supabase values.
const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
const char* SUPABASE_FUNCTION_URL = "https://YOUR_PROJECT_REF.functions.supabase.co/esp32-wifi";
const char* SUPABASE_ANON_KEY = "YOUR_SUPABASE_ANON_KEY";

const char* DEVICE_ID = "esp32-001";
const int LED_PIN = 2;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(500);
    Serial.print(".");
  }

  digitalWrite(LED_PIN, HIGH);
  Serial.println();
  Serial.print("Connected. IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    sendStatus();
  } else {
    digitalWrite(LED_PIN, LOW);
    WiFi.reconnect();
  }

  delay(10000);
}

void sendStatus() {
  HTTPClient http;
  http.begin(SUPABASE_FUNCTION_URL);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("apikey", SUPABASE_ANON_KEY);
  http.addHeader("Authorization", String("Bearer ") + SUPABASE_ANON_KEY);

  String payload = "{";
  payload += "\"deviceId\":\"" + String(DEVICE_ID) + "\",";
  payload += "\"ipAddress\":\"" + WiFi.localIP().toString() + "\",";
  payload += "\"rssi\":" + String(WiFi.RSSI());
  payload += "}";

  int statusCode = http.POST(payload);
  String response = http.getString();

  Serial.print("HTTP ");
  Serial.print(statusCode);
  Serial.print(": ");
  Serial.println(response);

  http.end();
}
