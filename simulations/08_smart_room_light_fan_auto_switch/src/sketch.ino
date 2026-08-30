/**
 * Simulation 08: Smart Room Auto Fan & Light Controller
 * Features:
 *  - PIR Motion Occupancy Detection
 *  - LDR Ambient Lux Gating (Light turns on only if dark)
 *  - DHT22 Temperature-Adaptive Fan Control (Auto ON > 28C)
 *  - 2x Physical Wall Rocker Switch Inputs (Instant 2-way toggle with sync)
 *  - Automatic Inactivity Switch-Off (Energy Saver when room is vacant)
 */

#include <Arduino.h>
#include <DHT.h>

// Pin Definitions
#define PIN_PIR        13
#define PIN_LDR        34
#define PIN_DHT        23
#define PIN_RELAY_LIGHT 19
#define PIN_RELAY_FAN   18
#define PIN_SW_LIGHT   25
#define PIN_SW_FAN     26

#define DHTTYPE DHT22
DHT dht(PIN_DHT, DHTTYPE);

// Configurable Thresholds & Timers
const unsigned long OCCUPANCY_TIMEOUT_MS = 15000; // 15s demo timeout (15 min in production)
const int LUX_DARK_THRESHOLD = 1800;             // Analog threshold (higher = darker)
const float FAN_TEMP_ON = 28.0;                  // Turn fan on above 28°C
const float FAN_TEMP_OFF = 26.5;                 // Turn fan off below 26.5°C (1.5°C hysteresis)

// State Variables
bool lightState = false;
bool fanState = false;
bool roomOccupied = false;
unsigned long lastMotionTime = 0;
unsigned long lastSensorReadTime = 0;

int lastSwLightVal = HIGH;
int lastSwFanVal = HIGH;

void setLight(bool state, const char* reason) {
  if (lightState != state) {
    lightState = state;
    digitalWrite(PIN_RELAY_LIGHT, lightState ? HIGH : LOW);
    Serial.printf("[LIGHT] Relay set to %s | Reason: %s\n", lightState ? "ON" : "OFF", reason);
  }
}

void setFan(bool state, const char* reason) {
  if (fanState != state) {
    fanState = state;
    digitalWrite(PIN_RELAY_FAN, fanState ? HIGH : LOW);
    Serial.printf("[FAN] Relay set to %s | Reason: %s\n", fanState ? "ON" : "OFF", reason);
  }
}

void checkManualSwitches() {
  int swLight = digitalRead(PIN_SW_LIGHT);
  if (swLight != lastSwLightVal) {
    delay(20); // Debounce
    if (digitalRead(PIN_SW_LIGHT) == swLight) {
      lastSwLightVal = swLight;
      setLight(!lightState, "Manual Wall Switch 1 Toggled");
      lastMotionTime = millis(); // Refresh occupancy on user interaction
    }
  }

  int swFan = digitalRead(PIN_SW_FAN);
  if (swFan != lastSwFanVal) {
    delay(20); // Debounce
    if (digitalRead(PIN_SW_FAN) == swFan) {
      lastSwFanVal = swFan;
      setFan(!fanState, "Manual Wall Switch 2 Toggled");
      lastMotionTime = millis();
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println("==================================================");
  Serial.println(" SMART ROOM LIGHT & FAN CONTROLLER INITIALIZED ");
  Serial.println(" Mode: Detached 2-Way Sync + Occupancy + Climate ");
  Serial.println("==================================================");

  pinMode(PIN_PIR, INPUT);
  pinMode(PIN_LDR, INPUT);
  pinMode(PIN_RELAY_LIGHT, OUTPUT);
  pinMode(PIN_RELAY_FAN, OUTPUT);
  pinMode(PIN_SW_LIGHT, INPUT_PULLUP);
  pinMode(PIN_SW_FAN, INPUT_PULLUP);

  digitalWrite(PIN_RELAY_LIGHT, LOW);
  digitalWrite(PIN_RELAY_FAN, LOW);

  dht.begin();
  lastMotionTime = millis();
}

void loop() {
  // 1. Process Physical Manual Wall Switches (Priority edge detection)
  checkManualSwitches();

  // 2. Read PIR Motion Sensor
  int pirVal = digitalRead(PIN_PIR);
  if (pirVal == HIGH) {
    if (!roomOccupied) {
      roomOccupied = true;
      Serial.println("\n[PRESENCE] Motion Detected! Room is now OCCUPIED.");
    }
    lastMotionTime = millis();
  }

  // 3. Periodic Sensor Evaluation (every 2 seconds)
  if (millis() - lastSensorReadTime >= 2000) {
    lastSensorReadTime = millis();

    int ldrRaw = analogRead(PIN_LDR);
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    if (isnan(temp) || isnan(hum)) {
      Serial.println("[WARN] DHT22 sensor read failure");
      temp = 25.0;
      hum = 50.0;
    }

    bool isDark = (ldrRaw > LUX_DARK_THRESHOLD);
    unsigned long timeSinceMotion = (millis() - lastMotionTime) / 1000;

    Serial.printf("[TELEMETRY] Temp: %.1f°C | Hum: %.1f%% | Lux ADC: %d (%s) | Occupied: %s (Idle: %lus)\n",
                  temp, hum, ldrRaw, isDark ? "DARK" : "BRIGHT",
                  roomOccupied ? "YES" : "NO", timeSinceMotion);

    // Automation Logic: Auto-ON when room occupied
    if (roomOccupied) {
      // Light auto-on only if room is dark
      if (isDark && !lightState) {
        setLight(true, "Occupancy Detected in Dark Room");
      }

      // Fan auto-on if temperature exceeds threshold
      if (temp >= FAN_TEMP_ON && !fanState) {
        setFan(true, "Occupancy & High Ambient Temperature");
      } else if (temp <= FAN_TEMP_OFF && fanState) {
        setFan(false, "Temperature Dropped Below Comfort Band");
      }
    }

    // Vacancy Logic: Auto-OFF when unoccupied for timeout duration
    if (millis() - lastMotionTime > OCCUPANCY_TIMEOUT_MS) {
      if (roomOccupied) {
        roomOccupied = false;
        Serial.println("[PRESENCE] Inactivity Timeout Reached. Room is VACANT.");
      }

      if (lightState) {
        setLight(false, "Energy Saver: Room Vacant Auto-Off");
      }
      if (fanState) {
        setFan(false, "Energy Saver: Room Vacant Auto-Off");
      }
    }
  }

  delay(50);
}
