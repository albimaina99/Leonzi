#include "DHT.h"
#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#include <HCSR04.h>
UltraSonicDistanceSensor distanceSensor(8, 9);  // TRIGGER, ECHO

unsigned long last_now = 0;


int delta = 1000;


int ledRed1 = 4;
int ledRed2 = 3;
int ledGreen = 2;


int button = 12;


int last_state = 0;


void setup() {

  Serial.begin(9600);
  Serial.println("TIME, PROSSIMITY, TEMPERATURE, RELATIVE HUMIDITY");
  dht.begin();
}

void loop() {

  unsigned long now = millis();
  if (now - last_now >= delta) {
    last_now = now;
    digitalWrite(ledGreen, HIGH);
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    int m = distanceSensor.measureDistanceCm();
    digitalWrite(ledGreen, LOW);

    Serial.print(now);
    Serial.print("ms,   ");
    Serial.print(m);
    Serial.print("cm,  ");
    Serial.print(t);
    Serial.print("°C,  ");
    Serial.print(h);
    Serial.println("%");
  }
  if (t > 30) {
    digitalWrite(ledRed1, HIGH);
  }
  if (h < 50) {
    digitalWrite(ledRed2, HIGH);
  }
  int state = digitalRead(button);
  if (state == 1 && last_state != state) {
    digitalWrite(ledRed1, LOW);
    digitalWrite(ledRed1, LOW);
  }
  last_state = state;
}










