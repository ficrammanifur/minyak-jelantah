#include <Arduino.h>
#include "HX711.h"

#define HX_DOUT 4
#define HX_SCK  5

HX711 scale;

void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.println();
  Serial.println("================================");
  Serial.println("HX711 READY TEST");
  Serial.println("================================");

  scale.begin(HX_DOUT, HX_SCK);

  pinMode(HX_SCK, OUTPUT);
  digitalWrite(HX_SCK, LOW);

  delay(1000);
}

void loop() {

  Serial.print("DOUT = ");
  Serial.print(digitalRead(HX_DOUT));

  Serial.print(" | READY = ");
  Serial.print(scale.is_ready() ? "YES" : "NO");

  if (scale.is_ready()) {
    long raw = scale.read();

    Serial.print(" | RAW = ");
    Serial.println(raw);
  } else {
    Serial.println();
  }

  delay(500);
}
