
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

const char ssid[] = "ssid";
const char pass[] = "password";
String apiKey = "api_thingspeak";

const int trigPin = 9;
const int echoPin = 10;

SoftwareSerial espSerial(2, 3); // RX, TX

void setup() {
  Serial.begin(9600);
  espSerial.begin(115200);
  connectToWiFi();
}

void loop() {
  long duration;
  int distance;

  // Ultrasuoni: misura la distanza
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distanza: ");
  Serial.println(distance);

  inviaDatiThingSpeak(distance);

  delay(10000);  // Attendere 10 secondi tra le letture
}

void connectToWiFi() {
  Serial.println("Connessione WiFi");

  espSerial.println("AT+RST"); // Reset ESP8266
  delay(1000);

  espSerial.println("AT+CWMODE=1"); // Imposta il modulo WiFi come stazione
  delay(1000);

  espSerial.print("AT+CWJAP=\"" + String(ssid) + "\",\"" + String(password) + "\""); // Connettiti al WiFi
  delay(2000);

  while (espSerial.available()) {
    Serial.write(espSerial.read());
  }

  Serial.println("Connesso a WiFi");
}

void inviaDatiThingSpeak(int distanza) {
  Serial.println("Invio dati a ThingSpeak...");

  HTTPClient http;

  String url = "http://api.thingspeak.com/update?api_key=" + apiKey + "&field1=" + String(distanza);

  http.begin(url);

  int httpCode = http.GET();

  if (httpCode > 0) {
    Serial.println("Dati inviati con successo a ThingSpeak");
  } else {
    Serial.println("Errore durante l'invio dei dati a ThingSpeak");
  }

  http.end();
}