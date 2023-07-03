#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <DHTesp.h>
#include <time.h> 

const char *WIFI_SSID = "GlobeAtHome_87BC8";
const char *WIFI_PASSWORD = "raymartwifi";
const char *FIREBASE_HOST = "paranfinal-default-rtdb.asia-southeast1.firebasedatabase.app";
const char *FIREBASE_AUTH = "4THqaMpr6Z5YHh9YRRijK9CsuWtAJgADrcgaVd7m";

FirebaseData firebaseData;

DHTesp dht;

void setup() {
  Serial.begin(115200);
  dht.setup(D2, DHTesp::DHT11);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  configTime(8 * 3600, 0, "pool.ntp.org", "time.nist.gov");

  while (time(nullptr) < 1000000000) {
    delay(100);
  }
}

void loop() {
  delay(dht.getMinimumSamplingPeriod());

  float h = dht.getHumidity();
  float t = dht.getTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  time_t now = time(nullptr);
  struct tm *timeinfo = localtime(&now);
  char timestamp[20];
  strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);

  String fireHumid = String(h);
  String fireTemp = String(t);
  String fireTimestamp = String(timestamp);

  Firebase.set(firebaseData, "/DHT11/Humidity", fireHumid);
  Firebase.set(firebaseData, "/DHT11/Temperature", fireTemp);
  Firebase.set(firebaseData, "/Timestamp", fireTimestamp);

  if (!firebaseData.errorReason().isEmpty()) {
    Serial.print("Error sending data to Firebase: ");
    Serial.println(firebaseData.errorReason());
  } else {
    Serial.print("Humidity: ");
    Serial.println(h);
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println("*C");
    Serial.print("Timestamp: ");
    Serial.println(timestamp);
    Serial.println("-----------------------------------------------------------------");
  }

  delay(2000); 
}
pool.ntp.org