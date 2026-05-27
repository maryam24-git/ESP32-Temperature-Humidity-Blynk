#define BLYNK_TEMPLATE_ID "TMPL6q8k08Nb5"
#define BLYNK_TEMPLATE_NAME "sending data"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// Pins according to the current Wokwi circuit
#define DHTPIN 15          // DHT22 data pin (Green wire)
#define DHTTYPE DHT22
#define LED_PIN 26         // LED control pin (Green wire)

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST"; // Wokwi virtual WiFi network
char pass[] = "";

// To control LED from the Blynk Dashboard
BLYNK_WRITE(V2) {
  int buttonState = param.asInt();

  if (buttonState == 1) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Blynk Notification: LED turned ON");
  } else {
    digitalWrite(LED_PIN, LOW);
    Serial.println("Blynk Notification: LED turned OFF");
  }
}

// Send sensor data to Blynk every 2 seconds
void sendDHTData() {

  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(h) || isnan(t)) {
    Serial.println("Error: Failed to read from DHT sensor!");
    return;
  }

  // Sending data to Blynk cloud virtual pins
  Blynk.virtualWrite(V0, t); // Temperature data to V0
  Blynk.virtualWrite(V1, h); // Humidity data to V1

  // Serial Monitor debugging
  Serial.print("Current Temp: ");
  Serial.print(t);
  Serial.print(" °C\t");

  Serial.print("Current Humidity: ");
  Serial.print(h);
  Serial.println(" %");
}

void setup() {

  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);

  dht.begin(); // Initialize DHT sensor

  // Initialize Blynk server and WiFi connection
  Blynk.begin(auth, ssid, pass);

  // Set timer to call function every 2000 milliseconds (2 seconds)
  timer.setInterval(2000L, sendDHTData);
}

void loop() {

  Blynk.run();
  timer.run();
}
