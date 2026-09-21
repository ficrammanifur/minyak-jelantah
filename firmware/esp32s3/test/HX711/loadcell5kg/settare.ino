#include <Arduino.h>
#include "HX711.h"

#define HX_DOUT 4
#define HX_SCK  5

HX711 scale;

void setup() {

  Serial.begin(115200);
  delay(3000);

  Serial.println();
  Serial.println("========================================");
  Serial.println("      HX711 LOAD CELL 5KG");
  Serial.println("      CALIBRATION TEST");
  Serial.println("========================================");

  scale.begin(HX_DOUT, HX_SCK);

  // Pastikan SCK LOW
  pinMode(HX_SCK, OUTPUT);
  digitalWrite(HX_SCK, LOW);

  Serial.println();
  Serial.println("Menunggu HX711 READY...");

  // Tunggu maksimal 10 detik
  unsigned long start = millis();

  while (!scale.is_ready()) {

    Serial.println("HX711 belum READY...");
    delay(500);

    if (millis() - start > 10000) {

      Serial.println();
      Serial.println("========================================");
      Serial.println("HX711 TIDAK READY SETELAH 10 DETIK");
      Serial.println("========================================");

      Serial.print("DOUT = ");
      Serial.println(digitalRead(HX_DOUT));

      while (1) {
        delay(1000);
      }
    }
  }

  Serial.println();
  Serial.println("HX711 READY!");

  // ========================================
  // TARE
  // ========================================

  Serial.println();
  Serial.println("KOSONGKAN LOAD CELL!");
  Serial.println("Tunggu 3 detik...");

  delay(3000);

  scale.set_scale(1.0);

  scale.tare(20);

  Serial.println();
  Serial.println("TARE SELESAI");

  Serial.print("OFFSET = ");
  Serial.println(scale.get_offset());

  Serial.println();
  Serial.println("========================================");
  Serial.println("SEKARANG TARUH BEBAN");
  Serial.println("========================================");

  Serial.println();
  Serial.println("Lihat berat pada timbangan digital.");
  Serial.println("Ketik berat ASLI dalam gram.");
  Serial.println();
  Serial.println("Contoh:");
  Serial.println("394");
  Serial.println();
  Serial.println("Tekan ENTER.");
}

void loop() {

  // ========================================
  // RAW MONITOR
  // ========================================

  if (scale.is_ready()) {

    long raw = scale.read();

    Serial.print("RAW = ");
    Serial.println(raw);

  } else {

    Serial.println("HX711 kehilangan READY!");
  }

  // ========================================
  // INPUT BERAT
  // ========================================

  if (Serial.available()) {

    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.length() > 0) {

      float known_weight = input.toFloat();

      if (known_weight <= 0) {

        Serial.println("Input tidak valid.");
        Serial.println("Contoh: 394");

        return;
      }

      Serial.println();
      Serial.println("========================================");
      Serial.println("KALIBRASI");
      Serial.println("========================================");

      Serial.print("Berat asli = ");
      Serial.print(known_weight, 2);
      Serial.println(" gram");

      delay(1000);

      long raw_value = scale.get_value(20);

      Serial.print("RAW setelah TARE = ");
      Serial.println(raw_value);

      // ====================================
      // HITUNG FACTOR
      // ====================================

      float calibration_factor =
        (float)raw_value / known_weight;

      Serial.println();

      Serial.print("CALIBRATION FACTOR = ");
      Serial.println(calibration_factor, 6);

      scale.set_scale(calibration_factor);

      Serial.println();
      Serial.println("HASIL:");

      for (int i = 0; i < 10; i++) {

        float weight = scale.get_units(5);

        Serial.print("Berat = ");
        Serial.print(weight, 2);
        Serial.println(" gram");

        delay(500);
      }

      Serial.println();
      Serial.println("========================================");
      Serial.println("SELESAI");
      Serial.println("========================================");
    }
  }

  delay(300);
}
