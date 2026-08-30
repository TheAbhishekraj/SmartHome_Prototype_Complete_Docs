/**
 * Simulation 11: Smart Video Doorbell, Panic Button & Fall Alarm Node
 * Features:
 *  - Doorbell Visitor Chime with 2-Tone Melodic Sequence
 *  - High-Priority Emergency Panic Button (Latched Alarm)
 *  - Elder Fall / Impact Detection Simulation
 *  - Emergency Alarm Strobe & Piercing Siren
 *  - Local Master Reset / Acknowledge Switch
 */

#include <Arduino.h>

#define PIN_BTN_DOORBELL  13
#define PIN_BTN_PANIC     14
#define PIN_BTN_FALL      27
#define PIN_BTN_RESET     26

#define PIN_LED_DOOR      19
#define PIN_LED_PANIC     18
#define PIN_BUZZER        23

bool panicLatched = false;
bool doorbellActive = false;
unsigned long doorbellStartTime = 0;
unsigned long lastTelemetryTime = 0;

void triggerPanic(const char* triggerSource) {
  if (!panicLatched) {
    panicLatched = true;
    Serial.printf("\n🚨 [EMERGENCY CRITICAL ALARM] Triggered by: %s\n", triggerSource);
    Serial.println("🚨 [ACTION] High-priority MQTT Alert Dispatched to Family & Cloud!");
  }
}

void resetPanic() {
  if (panicLatched) {
    panicLatched = false;
    digitalWrite(PIN_LED_PANIC, LOW);
    digitalWrite(PIN_BUZZER, LOW);
    Serial.println("\n✅ [ALARM RESET] Emergency cleared by Master Reset Switch.");
  }
}

void ringDoorbell() {
  if (!doorbellActive && !panicLatched) {
    doorbellActive = true;
    doorbellStartTime = millis();
    digitalWrite(PIN_LED_DOOR, HIGH);
    Serial.println("\n🔔 [DOORBELL] Visitor at Front Door! Ringing chime...");
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println("==================================================");
  Serial.println(" SMART DOORBELL & PANIC / FALL DETECTION NODE ");
  Serial.println(" Target: Front Door, Bedside & Elderly Fall Safety ");
  Serial.println("==================================================");

  pinMode(PIN_BTN_DOORBELL, INPUT_PULLUP);
  pinMode(PIN_BTN_PANIC, INPUT_PULLUP);
  pinMode(PIN_BTN_FALL, INPUT_PULLUP);
  pinMode(PIN_BTN_RESET, INPUT_PULLUP);

  pinMode(PIN_LED_DOOR, OUTPUT);
  pinMode(PIN_LED_PANIC, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);

  digitalWrite(PIN_LED_DOOR, LOW);
  digitalWrite(PIN_LED_PANIC, LOW);
  digitalWrite(PIN_BUZZER, LOW);
}

void loop() {
  // 1. Read Inputs (Active LOW with pull-up)
  if (digitalRead(PIN_BTN_PANIC) == LOW) {
    delay(20);
    if (digitalRead(PIN_BTN_PANIC) == LOW) {
      triggerPanic("Bedside / Wall Panic Button Pressed");
    }
  }

  if (digitalRead(PIN_BTN_FALL) == LOW) {
    delay(20);
    if (digitalRead(PIN_BTN_FALL) == LOW) {
      triggerPanic("Elder Fall / Sudden Impact Sensor");
    }
  }

  if (digitalRead(PIN_BTN_RESET) == LOW) {
    delay(20);
    if (digitalRead(PIN_BTN_RESET) == LOW) {
      resetPanic();
    }
  }

  if (digitalRead(PIN_BTN_DOORBELL) == LOW) {
    delay(20);
    if (digitalRead(PIN_BTN_DOORBELL) == LOW) {
      ringDoorbell();
    }
  }

  // 2. Alarm Output Logic
  if (panicLatched) {
    // Strobe Red LED and Pulsing Siren
    bool pulse = (millis() / 200) % 2;
    digitalWrite(PIN_LED_PANIC, pulse);
    digitalWrite(PIN_BUZZER, pulse);
  } else if (doorbellActive) {
    // 2-tone melodic doorbell chime simulation (3 seconds)
    unsigned long elapsed = millis() - doorbellStartTime;
    if (elapsed < 3000) {
      if (elapsed < 600 || (elapsed > 1000 && elapsed < 1600)) {
        digitalWrite(PIN_BUZZER, HIGH);
      } else {
        digitalWrite(PIN_BUZZER, LOW);
      }
    } else {
      doorbellActive = false;
      digitalWrite(PIN_LED_DOOR, LOW);
      digitalWrite(PIN_BUZZER, LOW);
      Serial.println("🔔 [DOORBELL] Chime cycle completed.");
    }
  } else {
    digitalWrite(PIN_LED_DOOR, LOW);
    digitalWrite(PIN_LED_PANIC, LOW);
    digitalWrite(PIN_BUZZER, LOW);
  }

  // 3. Periodic Telemetry (every 2.5 seconds)
  if (millis() - lastTelemetryTime >= 2500) {
    lastTelemetryTime = millis();
    Serial.printf("[SECURITY STATUS] Doorbell: %-6s | Panic Latch: %-7s | Fall Sensor: ARMED\n",
                  doorbellActive ? "RING" : "IDLE",
                  panicLatched ? "ALARM!" : "CLEAR");
  }

  delay(30);
}
