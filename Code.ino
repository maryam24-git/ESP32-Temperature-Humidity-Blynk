#define BLYNK_TEMPLATE_ID "TMPL6q8k08Nb5"
#define BLYNK_TEMPLATE_NAME "sending data"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// Wokwi ke current circuit ke mutabiq pins
#define DHTPIN 15          // DHT22 data pin (Green wire)
#define DHTTYPE DHT22
#define LED_PIN 26         // LED control pin (Green wire)

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST"; // Wokwi virtual WiFi network
char pass[] = "";

// Blynk Dashboard se LED control karne ke liye
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

// Sensor ka data har 2 second baad Blynk par bhejte hain
void sendDHTData() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Error: Failed to read from DHT sensor!");
    return;
  }

  // Blynk cloud par custom datastreams par write kar rahe hain
  Blynk.virtualWrite(V0, t); // Temperature data to V0
  Blynk.virtualWrite(V1, h); // Humidity data to V1

  // Serial monitor debugging ke liye
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
  
  dht.begin(); // DHT sensor active ho gaya
  
  // Blynk server aur virtual WiFi configuration init
  Blynk.begin(auth, ssid, pass);
  
  // 2000 milliseconds (2 seconds) ka loop timer setup
  timer.setInterval(2000L, sendDHTData);
}

void loop() {
  Blynk.run();
  timer.run();
}
