/**
 * Simulation 10: Indoor Air Quality Monitor & Automated Exhaust Fan
 * Features:
 *  - MQ-135 Air Quality Sensor Simulation (0 - 2000 PPM CO2/VOC/Smoke)
 *  - Automated Exhaust Fan Relay Trigger with Hysteresis & Minimum Purge Timer
 *  - 3-Stage Air Quality Status LEDs (Green: Good, Yellow: Moderate, Red: Hazardous)
 *  - Audible Hazard Warning Alarm (> 1400 PPM)
 */

#include <Arduino.h>

#define PIN_SENSOR_AIR  34
#define PIN_RELAY_FAN   19
#define PIN_LED_GOOD    18
#define PIN_LED_MOD     5
#define PIN_LED_BAD     17
#define PIN_BUZZER      23

// Threshold Constants (PPM)
const int PPM_GOOD_MAX = 400;       // < 400 PPM = Clean / Good
const int PPM_FAN_TRIGGER = 600;    // > 600 PPM = Auto Turn Fan ON
const int PPM_MOD_MAX = 800;        // 400 - 800 PPM = Moderate
const int PPM_HAZARDOUS = 1400;     // > 1400 PPM = Sound Buzzer

const unsigned long MIN_PURGE_MS = 6000; // 6s minimum run cycle

bool fanRunning = false;
unsigned long fanStartTime = 0;
unsigned long lastLogTime = 0;

void setFan(bool state, const char* reason) {
  if (fanRunning != state) {
    fanRunning = state;
    digitalWrite(PIN_RELAY_FAN, fanRunning ? HIGH : LOW);
    if (fanRunning) fanStartTime = millis();
    Serial.printf("[EXHAUST FAN] Relay %s | Reason: %s\n", fanRunning ? "ACTIVATED" : "DEACTIVATED", reason);
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println("==================================================");
  Serial.println(" INDOOR AIR QUALITY & AUTO EXHAUST CONTROLLER ");
  Serial.println(" Target: Kitchen / Washroom / Living Room IAQ ");
  Serial.println("==================================================");

  pinMode(PIN_SENSOR_AIR, INPUT);
  pinMode(PIN_RELAY_FAN, OUTPUT);
  pinMode(PIN_LED_GOOD, OUTPUT);
  pinMode(PIN_LED_MOD, OUTPUT);
  pinMode(PIN_LED_BAD, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);

  digitalWrite(PIN_RELAY_FAN, LOW);
  digitalWrite(PIN_LED_GOOD, HIGH);
  digitalWrite(PIN_LED_MOD, LOW);
  digitalWrite(PIN_LED_BAD, LOW);
  digitalWrite(PIN_BUZZER, LOW);
}

void loop() {
  int rawADC = analogRead(PIN_SENSOR_AIR);
  int ppm = map(rawADC, 0, 4095, 200, 2000);

  // Status LED Management
  if (ppm <= PPM_GOOD_MAX) {
    digitalWrite(PIN_LED_GOOD, HIGH);
    digitalWrite(PIN_LED_MOD, LOW);
    digitalWrite(PIN_LED_BAD, LOW);
    digitalWrite(PIN_BUZZER, LOW);
  } else if (ppm <= PPM_MOD_MAX) {
    digitalWrite(PIN_LED_GOOD, LOW);
    digitalWrite(PIN_LED_MOD, HIGH);
    digitalWrite(PIN_LED_BAD, LOW);
    digitalWrite(PIN_BUZZER, LOW);
  } else {
    digitalWrite(PIN_LED_GOOD, LOW);
    digitalWrite(PIN_LED_MOD, LOW);
    digitalWrite(PIN_LED_BAD, HIGH);

    if (ppm >= PPM_HAZARDOUS) {
      digitalWrite(PIN_BUZZER, (millis() / 250) % 2); // Pulsed alarm
    } else {
      digitalWrite(PIN_BUZZER, LOW);
    }
  }

  // Automation Logic for Exhaust Fan
  if (ppm >= PPM_FAN_TRIGGER) {
    if (!fanRunning) {
      setFan(true, "Air Quality Exceeded 600 PPM Trigger");
    }
  } else if (ppm < PPM_GOOD_MAX && fanRunning) {
    // Check if minimum purge timer has elapsed
    if (millis() - fanStartTime >= MIN_PURGE_MS) {
      setFan(false, "Air Quality Restored to Clean Level (<400 PPM)");
    }
  }

  // Periodic Logging (every 1 second)
  if (millis() - lastLogTime >= 1000) {
    lastLogTime = millis();
    const char* statusStr = (ppm <= PPM_GOOD_MAX) ? "GOOD" : (ppm <= PPM_MOD_MAX ? "MODERATE" : "HAZARDOUS");
    Serial.printf("[IAQ] ADC: %4d | PPM: %4d (%-9s) | Exhaust Relay: %s\n",
                  rawADC, ppm, statusStr, fanRunning ? "RUNNING" : "OFF");
  }

  delay(50);
}
