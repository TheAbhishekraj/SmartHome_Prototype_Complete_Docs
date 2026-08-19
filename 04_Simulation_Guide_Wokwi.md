# 04_Simulation_Guide_Wokwi.md
# SmartHome Prototype — Wokwi Simulation Guide

**Version:** 1.0 | **Date:** August 2026

---

## Table of Contents
1. [Why Simulate First?](#1-why-simulate-first)
2. [Wokwi Basics](#2-wokwi-basics)
3. [Simulation 1: PIR Motion Light](#simulation-1-pir-motion-light)
4. [Simulation 2: DHT22 Temperature & Fan Control](#simulation-2-dht22-temperature--fan-control)
5. [Simulation 3: Soil Moisture & Water Pump](#simulation-3-soil-moisture--water-pump)
6. [Simulation 4: Gas Leak Detection & Alarm](#simulation-4-gas-leak-detection--alarm)
7. [Simulation 5: Ultrasonic Tank Level](#simulation-5-ultrasonic-tank-level)
8. [Simulation 6: ESP32-CAM Video Stream](#simulation-6-esp32-cam-video-stream)
9. [Simulation 7: Stepper Motor Curtain](#simulation-7-stepper-motor-curtain)
10. [Simulation 8: ACS712 Current Monitoring](#simulation-8-acs712-current-monitoring)
11. [Simulation 9: IR Blaster for AC Control](#simulation-9-ir-blaster-for-ac-control)
12. [Simulation 10: Reed Switch Door Monitor](#simulation-10-reed-switch-door-monitor)
13. [Testing MQTT in Simulation](#testing-mqtt-in-simulation)
14. [Tinkercad Alternative](#tinkercad-alternative)

---

## 1. Why Simulate First?

| Benefit | Explanation |
|---------|-------------|
| **No hardware cost** | Test logic before buying components |
| **No fire risk** | Mains circuits tested virtually |
| **Fast iteration** | Change code → see result in seconds |
| **Logic validation** | Verify thresholds, timing, state machines |
| **Documentation** | Simulated circuits become build references |
| **Team sharing** | Share Wokwi links with collaborators |

**Rule:** Every node type MUST be simulated before breadboard testing.

---

## 2. Wokwi Basics

**URL:** https://wokwi.com

### Getting Started
1. Go to wokwi.com → "Start from Scratch" → Select "ESP32"
2. Add components from left sidebar (sensors, displays, etc.)
3. Wire by clicking pins
4. Write code in editor
5. Click "Start Simulation"

### Pro Tips
- **Serial Monitor:** Built-in, shows Serial.print() output
- **Interactive Controls:** Click on sensors to change values (e.g., drag LDR to change light)
- **Diagram.json:** Export/import circuit definitions
- **Libraries:** Wokwi supports Arduino framework natively

### Limitations
- No ESPHome YAML support directly (use Arduino C++ for logic testing)
- Some sensors simplified (e.g., MQ-6 gas sensor is simulated as analog input)
- No real WiFi/MQTT (use Serial.print to verify MQTT payload strings)
- No camera simulation for ESP32-CAM

---

## Simulation 1: PIR Motion Light

**Purpose:** Test PIR → Relay → Light logic with adjustable delay

### Wokwi Link
https://wokwi.com/projects/new/esp32

### Circuit (Diagram.json)
```json
{
  "version": 1,
  "author": "SmartHome Project",
  "parts": [
    { "type": "board-esp32-devkit-c-v4", "id": "esp", "top": 0, "left": 0 },
    { "type": "wokwi-pir-motion-sensor", "id": "pir", "top": -50, "left": 150 },
    { "type": "wokwi-led", "id": "led", "top": 100, "left": 150 },
    { "type": "wokwi-resistor", "id": "r1", "top": 80, "left": 200, "attrs": { "value": "220" } }
  ],
  "connections": [
    [ "esp:3V3", "pir:VCC", "red", [ "v0" ] ],
    [ "esp:GND.2", "pir:GND", "black", [ "v0" ] ],
    [ "esp:23", "pir:OUT", "blue", [ "v0" ] ],
    [ "esp:19", "led:A", "green", [ "v0" ] ],
    [ "led:C", "r1:1", "black", [ "v0" ] ],
    [ "r1:2", "esp:GND.2", "black", [ "v0" ] ]
  ]
}
```

### Test Code (Arduino)
```cpp
// PIR Motion Light Simulation
// Tests: motion detection, light ON delay, auto OFF timer

const int PIR_PIN = 23;
const int RELAY_PIN = 19;  // Simulated by LED

// TUNABLE PARAMETERS
int MOTION_TIMEOUT = 30000;    // Light stays ON for 30 sec after motion (ms)
bool TRIGGER_ON_RISING = true; // true = trigger on motion start only

unsigned long lastMotionTime = 0;
bool lightOn = false;

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  Serial.println("PIR Motion Light Sim Started");
  Serial.println("Click PIR sensor in Wokwi to simulate motion");
}

void loop() {
  int motion = digitalRead(PIR_PIN);

  if (motion == HIGH) {
    lastMotionTime = millis();
    if (!lightOn) {
      digitalWrite(RELAY_PIN, HIGH);
      lightOn = true;
      Serial.println("[EVENT] Motion detected → Light ON");
    }
  }

  if (lightOn && (millis() - lastMotionTime > MOTION_TIMEOUT)) {
    digitalWrite(RELAY_PIN, LOW);
    lightOn = false;
    Serial.println("[EVENT] Timeout → Light OFF");
  }

  delay(100);
}
```

### What to Test
1. Click PIR → LED turns ON → Serial confirms
2. Wait 30 seconds → LED turns OFF automatically
3. Click PIR again within 30 seconds → timer resets
4. Change `MOTION_TIMEOUT` to 5000 → test faster cycles

---

## Simulation 2: DHT22 Temperature & Fan Control

**Purpose:** Test temperature thresholds, hysteresis, fan control

### Wokwi Link
https://wokwi.com/projects/new/esp32

### Circuit
```json
{
  "version": 1,
  "parts": [
    { "type": "board-esp32-devkit-c-v4", "id": "esp", "top": 0, "left": 0 },
    { "type": "wokwi-dht22", "id": "dht", "top": -30, "left": 150 },
    { "type": "wokwi-led", "id": "fan", "top": 100, "left": 150 },
    { "type": "wokwi-resistor", "id": "r1", "top": 80, "left": 200, "attrs": { "value": "220" } }
  ],
  "connections": [
    [ "esp:3V3", "dht:VCC", "red", [ "v0" ] ],
    [ "esp:GND.2", "dht:GND", "black", [ "v0" ] ],
    [ "esp:21", "dht:SDA", "blue", [ "v0" ] ],
    [ "esp:19", "fan:A", "green", [ "v0" ] ],
    [ "fan:C", "r1:1", "black", [ "v0" ] ],
    [ "r1:2", "esp:GND.2", "black", [ "v0" ] ]
  ]
}
```

### Test Code
```cpp
#include <DHT.h>

#define DHT_PIN 21
#define FAN_PIN 19
#define DHT_TYPE DHT22

// TUNABLE THRESHOLDS
float TEMP_ON = 28.0;      // Turn fan ON above this (°C)
float TEMP_OFF = 26.0;     // Turn fan OFF below this (°C)
float HUMIDITY_MAX = 70.0; // Turn fan ON if humidity > this (%)
int READ_INTERVAL = 5000;  // Read sensor every 5 seconds

DHT dht(DHT_PIN, DHT_TYPE);
bool fanRunning = false;

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(FAN_PIN, OUTPUT);
  Serial.println("DHT22 Climate Control Sim Started");
  Serial.println("Click DHT sensor in Wokwi to change temp/humidity");
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("[ERROR] DHT read failed!");
    delay(READ_INTERVAL);
    return;
  }

  Serial.print("Temp: "); Serial.print(temp);
  Serial.print("°C  Humidity: "); Serial.print(hum); Serial.println("%");

  // Hysteresis logic: ON at 28°C, OFF at 26°C
  if (temp >= TEMP_ON || hum >= HUMIDITY_MAX) {
    if (!fanRunning) {
      digitalWrite(FAN_PIN, HIGH);
      fanRunning = true;
      Serial.println("[ACTION] Fan ON (Temp/Humidity threshold)");
    }
  } else if (temp <= TEMP_OFF && hum < HUMIDITY_MAX - 5.0) {
    if (fanRunning) {
      digitalWrite(FAN_PIN, LOW);
      fanRunning = false;
      Serial.println("[ACTION] Fan OFF (Temp/Humidity normal)");
    }
  }

  delay(READ_INTERVAL);
}
```

### What to Test
1. Set temp to 30°C in Wokwi → Fan turns ON
2. Set temp to 25°C → Fan stays ON until below 26°C (hysteresis)
3. Set humidity to 75% → Fan turns ON regardless of temp
4. Set humidity to 60% + temp 25°C → Fan turns OFF

---

## Simulation 3: Soil Moisture & Water Pump

**Purpose:** Test soil moisture threshold, pump ON time, anti-flood timer

### Circuit
```json
{
  "version": 1,
  "parts": [
    { "type": "board-esp32-devkit-c-v4", "id": "esp", "top": 0, "left": 0 },
    { "type": "wokwi-hc-sr04", "id": "ultra", "top": -50, "left": 150 },
    { "type": "wokwi-led", "id": "pump", "top": 100, "left": 150 },
    { "type": "wokwi-resistor", "id": "r1", "top": 80, "left": 200, "attrs": { "value": "220" } },
    { "type": "wokwi-potentiometer", "id": "soil", "top": -50, "left": -80 }
  ],
  "connections": [
    [ "esp:3V3", "soil:VCC", "red", [ "v0" ] ],
    [ "esp:GND.2", "soil:GND", "black", [ "v0" ] ],
    [ "esp:34", "soil:SIG", "blue", [ "v0" ] ],
    [ "esp:19", "pump:A", "green", [ "v0" ] ],
    [ "pump:C", "r1:1", "black", [ "v0" ] ],
    [ "r1:2", "esp:GND.2", "black", [ "v0" ] ]
  ]
}
```

### Test Code
```cpp
const int SOIL_PIN = 34;      // Analog input (potentiometer simulates moisture)
const int PUMP_PIN = 19;      // Relay output

// TUNABLE PARAMETERS
int DRY_THRESHOLD = 3000;     // ADC value below this = dry (0-4095 for ESP32)
int WET_THRESHOLD = 1500;     // ADC value above this = wet enough
unsigned long PUMP_MAX_TIME = 10000;  // Max pump ON time: 10 seconds
unsigned long PUMP_COOLDOWN = 300000; // Wait 5 min between watering

unsigned long pumpStartTime = 0;
unsigned long lastWatering = 0;
bool pumpRunning = false;

void setup() {
  Serial.begin(115200);
  pinMode(PUMP_PIN, OUTPUT);
  analogReadResolution(12);  // 0-4095
  Serial.println("Soil Moisture & Pump Sim Started");
  Serial.println("Adjust potentiometer to simulate soil moisture");
}

void loop() {
  int moisture = analogRead(SOIL_PIN);
  Serial.print("Soil Moisture ADC: "); Serial.println(moisture);

  // Safety: Anti-flood timer
  if (pumpRunning && (millis() - pumpStartTime > PUMP_MAX_TIME)) {
    digitalWrite(PUMP_PIN, LOW);
    pumpRunning = false;
    Serial.println("[SAFETY] Pump auto-stopped (max time exceeded)");
  }

  // Watering logic
  if (moisture > DRY_THRESHOLD && !pumpRunning && 
      (millis() - lastWatering > PUMP_COOLDOWN)) {
    digitalWrite(PUMP_PIN, HIGH);
    pumpRunning = true;
    pumpStartTime = millis();
    lastWatering = millis();
    Serial.println("[ACTION] Pump STARTED — soil dry");
  }

  // Stop when wet enough
  if (pumpRunning && moisture < WET_THRESHOLD) {
    digitalWrite(PUMP_PIN, LOW);
    pumpRunning = false;
    Serial.println("[ACTION] Pump STOPPED — soil wet enough");
  }

  delay(1000);
}
```

### What to Test
1. Set pot to low value (dry) → Pump turns ON
2. Set pot to high value (wet) → Pump turns OFF
3. Verify pump stops after 10 seconds even if still dry (safety)
4. Verify pump won't restart for 5 minutes (cooldown)

---

## Simulation 4: Gas Leak Detection & Alarm

**Purpose:** Test gas threshold, alarm logic, relay sequencing

### Circuit
```json
{
  "version": 1,
  "parts": [
    { "type": "board-esp32-devkit-c-v4", "id": "esp", "top": 0, "left": 0 },
    { "type": "wokwi-potentiometer", "id": "gas", "top": -50, "left": 150 },
    { "type": "wokwi-buzzer", "id": "siren", "top": 100, "left": 150 },
    { "type": "wokwi-led", "id": "exhaust", "top": 100, "left": 200 },
    { "type": "wokwi-led", "id": "valve", "top": 100, "left": 250 }
  ],
  "connections": [
    [ "esp:3V3", "gas:VCC", "red", [ "v0" ] ],
    [ "esp:GND.2", "gas:GND", "black", [ "v0" ] ],
    [ "esp:34", "gas:SIG", "blue", [ "v0" ] ],
    [ "esp:18", "siren:1", "red", [ "v0" ] ],
    [ "siren:2", "esp:GND.2", "black", [ "v0" ] ],
    [ "esp:19", "exhaust:A", "green", [ "v0" ] ],
    [ "exhaust:C", "esp:GND.2", "black", [ "v0" ] ],
    [ "esp:21", "valve:A", "yellow", [ "v0" ] ],
    [ "valve:C", "esp:GND.2", "black", [ "v0" ] ]
  ]
}
```

### Test Code
```cpp
const int GAS_PIN = 34;
const int SIREN_PIN = 18;
const int EXHAUST_PIN = 19;
const int VALVE_PIN = 21;

// TUNABLE PARAMETERS
int GAS_THRESHOLD = 2000;      // ADC value above this = GAS LEAK
int GAS_CONFIRMATION = 3000;   // Must stay above threshold for 3 seconds
unsigned long ALARM_DURATION = 60000;  // Siren for 1 minute

int gasReadings[10];
int readingIndex = 0;
bool alarmActive = false;
unsigned long alarmStartTime = 0;

void setup() {
  Serial.begin(115200);
  pinMode(SIREN_PIN, OUTPUT);
  pinMode(EXHAUST_PIN, OUTPUT);
  pinMode(VALVE_PIN, OUTPUT);
  analogReadResolution(12);
  Serial.println("GAS LEAK DETECTION SIM STARTED");
  Serial.println("Adjust potentiometer to simulate gas concentration");
}

void loop() {
  int gasRaw = analogRead(GAS_PIN);

  // Moving average for noise reduction
  gasReadings[readingIndex] = gasRaw;
  readingIndex = (readingIndex + 1) % 10;
  int gasAvg = 0;
  for (int i = 0; i < 10; i++) gasAvg += gasReadings[i];
  gasAvg /= 10;

  Serial.print("Gas ADC: "); Serial.print(gasRaw);
  Serial.print("  Avg: "); Serial.println(gasAvg);

  // Gas leak detection with confirmation
  if (gasAvg > GAS_THRESHOLD && !alarmActive) {
    // Check if consistently high
    bool confirmed = true;
    for (int i = 0; i < 10; i++) {
      if (gasReadings[i] <= GAS_THRESHOLD) { confirmed = false; break; }
    }

    if (confirmed) {
      alarmActive = true;
      alarmStartTime = millis();

      // SAFETY SEQUENCE: Exhaust ON → Valve OFF → Siren ON
      digitalWrite(EXHAUST_PIN, HIGH);
      Serial.println("[CRITICAL] Exhaust fan ON");
      delay(500);
      digitalWrite(VALVE_PIN, HIGH);  // Simulates gas valve CLOSED
      Serial.println("[CRITICAL] Gas valve CLOSED");
      delay(500);
      digitalWrite(SIREN_PIN, HIGH);
      Serial.println("[CRITICAL] SIREN ACTIVATED");
      Serial.println("[ALERT] MQTT: gas_leak_detected = true");
    }
  }

  // Auto-reset after duration (or manual reset in real system)
  if (alarmActive && (millis() - alarmStartTime > ALARM_DURATION)) {
    digitalWrite(SIREN_PIN, LOW);
    Serial.println("[INFO] Siren auto-stopped (duration expired)");
    // Exhaust and valve stay in safe position until manual reset
  }

  // Manual reset simulation: set pot to 0
  if (alarmActive && gasAvg < 500) {
    alarmActive = false;
    digitalWrite(SIREN_PIN, LOW);
    digitalWrite(EXHAUST_PIN, LOW);
    digitalWrite(VALVE_PIN, LOW);  // Valve OPEN
    Serial.println("[RESET] Gas cleared. System reset.");
  }

  delay(500);
}
```

### What to Test
1. Slowly increase pot → verify 10-sample averaging
2. Cross threshold → verify sequence: Exhaust → Valve → Siren
3. Verify siren stops after 1 minute but safety state persists
4. Set pot to 0 → verify full reset

---

## Simulation 5: Ultrasonic Tank Level

**Purpose:** Test tank level calculation, pump control, dry-run protection

### Circuit
```json
{
  "version": 1,
  "parts": [
    { "type": "board-esp32-devkit-c-v4", "id": "esp", "top": 0, "left": 0 },
    { "type": "wokwi-hc-sr04", "id": "ultra", "top": -50, "left": 150 },
    { "type": "wokwi-potentiometer", "id": "current", "top": -50, "left": -80 },
    { "type": "wokwi-led", "id": "pump", "top": 100, "left": 150 },
    { "type": "wokwi-led", "id": "alert", "top": 100, "left": 200, "attrs": { "color": "red" } }
  ],
  "connections": [
    [ "esp:5", "ultra:TRIG", "blue", [ "v0" ] ],
    [ "esp:18", "ultra:ECHO", "green", [ "v0" ] ],
    [ "esp:3V3", "ultra:VCC", "red", [ "v0" ] ],
    [ "esp:GND.2", "ultra:GND", "black", [ "v0" ] ],
    [ "esp:34", "current:SIG", "orange", [ "v0" ] ],
    [ "esp:19", "pump:A", "green", [ "v0" ] ],
    [ "pump:C", "esp:GND.2", "black", [ "v0" ] ],
    [ "esp:21", "alert:A", "red", [ "v0" ] ],
    [ "alert:C", "esp:GND.2", "black", [ "v0" ] ]
  ]
}
```

### Test Code
```cpp
const int TRIG_PIN = 5;
const int ECHO_PIN = 18;
const int PUMP_PIN = 19;
const int ALERT_PIN = 21;
const int CURRENT_PIN = 34;  // Simulated by potentiometer

// TUNABLE PARAMETERS
float TANK_HEIGHT_CM = 100.0;    // Total tank height
float PUMP_ON_LEVEL = 80.0;      // Start pump when water below this %
float PUMP_OFF_LEVEL = 95.0;     // Stop pump when water reaches this %
float DRY_RUN_CURRENT = 500;   // ADC value below this = dry run
unsigned long DRY_RUN_TIME = 5000; // Check current after 5 sec

float currentLevel = 0;
bool pumpRunning = false;
unsigned long pumpStartTime = 0;
bool dryRunDetected = false;

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(ALERT_PIN, OUTPUT);
  analogReadResolution(12);
  Serial.println("Tank Level & Pump Control Sim Started");
}

float readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;  // cm
}

void loop() {
  float distance = readDistance();
  float levelPercent = 100.0 - ((distance / TANK_HEIGHT_CM) * 100.0);
  levelPercent = constrain(levelPercent, 0, 100);

  int currentRaw = analogRead(CURRENT_PIN);

  Serial.print("Distance: "); Serial.print(distance);
  Serial.print("cm  Level: "); Serial.print(levelPercent);
  Serial.print("%  Current ADC: "); Serial.println(currentRaw);

  // Dry-run protection
  if (pumpRunning && (millis() - pumpStartTime > DRY_RUN_TIME)) {
    if (currentRaw < DRY_RUN_CURRENT) {
      digitalWrite(PUMP_PIN, LOW);
      pumpRunning = false;
      dryRunDetected = true;
      digitalWrite(ALERT_PIN, HIGH);
      Serial.println("[CRITICAL] DRY RUN DETECTED! Pump STOPPED.");
      Serial.println("[ALERT] MQTT: dry_run_alert = true");
    }
  }

  // Pump control logic
  if (!dryRunDetected && levelPercent < PUMP_ON_LEVEL && !pumpRunning) {
    digitalWrite(PUMP_PIN, HIGH);
    pumpRunning = true;
    pumpStartTime = millis();
    Serial.println("[ACTION] Pump STARTED — tank low");
  }

  if (pumpRunning && levelPercent >= PUMP_OFF_LEVEL) {
    digitalWrite(PUMP_PIN, LOW);
    pumpRunning = false;
    Serial.println("[ACTION] Pump STOPPED — tank full");
  }

  delay(1000);
}
```

### What to Test
1. Simulate empty tank (large distance) → Pump starts
2. Simulate full tank (small distance) → Pump stops
3. Set current pot low after pump starts → Dry run detected → Alert
4. Verify pump won't restart automatically after dry run (needs manual reset)

---

## Simulation 6: ESP32-CAM Video Stream

**Note:** Wokwi does NOT simulate camera. Use this to test:
- WiFi connection code
- LED flash control
- PIR trigger logic

### Test Code (Arduino)
```cpp
#include <WiFi.h>

const int PIR_PIN = 13;
const int LED_PIN = 4;

// TUNABLE
int WIFI_TIMEOUT = 10000;

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  WiFi.begin("SmartHome_IoT", "YourPassword");
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < WIFI_TIMEOUT) {
    delay(500); Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("
WiFi Connected!");
    Serial.print("IP: "); Serial.println(WiFi.localIP());
  } else {
    Serial.println("
WiFi FAILED — check credentials");
  }
}

void loop() {
  if (digitalRead(PIR_PIN) == HIGH) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("[EVENT] Motion → IR LED ON (night mode)");
    delay(5000);
    digitalWrite(LED_PIN, LOW);
  }
  delay(100);
}
```

---

## Simulation 7: Stepper Motor Curtain

### Circuit
```json
{
  "version": 1,
  "parts": [
    { "type": "board-esp32-devkit-c-v4", "id": "esp", "top": 0, "left": 0 },
    { "type": "wokwi-stepper-motor", "id": "stepper", "top": 50, "left": 150 },
    { "type": "wokwi-a4988", "id": "driver", "top": -30, "left": 150 }
  ],
  "connections": [
    [ "esp:18", "driver:STEP", "blue", [ "v0" ] ],
    [ "esp:19", "driver:DIR", "green", [ "v0" ] ],
    [ "esp:3V3", "driver:VDD", "red", [ "v0" ] ],
    [ "esp:GND.2", "driver:GND", "black", [ "v0" ] ],
    [ "driver:1B", "stepper:B+", "orange", [ "v0" ] ],
    [ "driver:1A", "stepper:B-", "orange", [ "v0" ] ],
    [ "driver:2A", "stepper:A-", "blue", [ "v0" ] ],
    [ "driver:2B", "stepper:A+", "blue", [ "v0" ] ]
  ]
}
```

### Test Code
```cpp
const int STEP_PIN = 18;
const int DIR_PIN = 19;

// TUNABLE
int STEPS_PER_REV = 2048;    // 28BYJ-48
int CURTAIN_STEPS = 4096;    // Full open/close
int STEP_DELAY_MS = 2;       // Speed

void setup() {
  Serial.begin(115200);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  Serial.println("Curtain Motor Sim Started");
}

void moveCurtain(bool open) {
  digitalWrite(DIR_PIN, open ? HIGH : LOW);
  Serial.println(open ? "[ACTION] Opening curtain..." : "[ACTION] Closing curtain...");

  for (int i = 0; i < CURTAIN_STEPS; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delay(STEP_DELAY_MS);
    digitalWrite(STEP_PIN, LOW);
    delay(STEP_DELAY_MS);
  }
  Serial.println("[DONE] Curtain movement complete");
}

void loop() {
  // Simulate morning open
  moveCurtain(true);
  delay(5000);
  // Simulate night close
  moveCurtain(false);
  delay(5000);
}
```

---

## Simulation 8: ACS712 Current Monitoring

### Test Code
```cpp
const int CURRENT_PIN = 34;

// TUNABLE
float VCC = 3.3;
float ACS_OFFSET = VCC / 2;  // 1.65V at 0A
float SENSITIVITY = 0.100;   // 100mV/A for 20A module
int SAMPLES = 1000;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);
  Serial.println("ACS712 Current Monitor Sim Started");
}

void loop() {
  float sum = 0;
  for (int i = 0; i < SAMPLES; i++) {
    sum += analogRead(CURRENT_PIN);
  }
  float avgADC = sum / SAMPLES;
  float voltage = (avgADC / 4095.0) * VCC;
  float current = (voltage - ACS_OFFSET) / SENSITIVITY;

  Serial.print("ADC: "); Serial.print(avgADC);
  Serial.print("  Voltage: "); Serial.print(voltage, 3);
  Serial.print("V  Current: "); Serial.print(current, 2);
  Serial.println("A");

  delay(1000);
}
```

---

## Simulation 9: IR Blaster for AC Control

**Note:** Wokwi has no IR LED simulation. Test by verifying GPIO toggles and timing.

```cpp
const int IR_LED = 19;

// Simulated: Send "Power ON" NEC protocol signal
// Real implementation uses IRsend library

void sendNEC(unsigned long data, int nbits) {
  // NEC: 9ms lead HIGH, 4.5ms lead LOW, then data
  Serial.print("[IR] Sending NEC code: 0x");
  Serial.println(data, HEX);
  // In real code: irsend.sendNEC(data, nbits);
}

void setup() {
  Serial.begin(115200);
  pinMode(IR_LED, OUTPUT);
  Serial.println("IR Blaster Sim — Learn your AC remote codes first!");
}

void loop() {
  sendNEC(0x20DF10EF, 32);  // Example NEC code
  delay(5000);
}
```

---

## Simulation 10: Reed Switch Door Monitor

```cpp
const int REED_PIN = 23;
const int LED_PIN = 19;

// TUNABLE
unsigned long OPEN_ALERT_DELAY = 30000;  // Alert if open >30 sec at night

bool doorOpen = false;
unsigned long openTime = 0;

void setup() {
  Serial.begin(115200);
  pinMode(REED_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("Door Monitor Sim Started");
}

void loop() {
  bool isOpen = digitalRead(REED_PIN) == LOW;  // NC switch

  if (isOpen && !doorOpen) {
    doorOpen = true;
    openTime = millis();
    digitalWrite(LED_PIN, HIGH);
    Serial.println("[EVENT] Door OPENED");
  }

  if (!isOpen && doorOpen) {
    doorOpen = false;
    digitalWrite(LED_PIN, LOW);
    Serial.println("[EVENT] Door CLOSED");
  }

  if (doorOpen && (millis() - openTime > OPEN_ALERT_DELAY)) {
    Serial.println("[ALERT] Door left open for >30 seconds!");
    // Reset timer to avoid spam
    openTime = millis();
  }

  delay(100);
}
```

---

## Testing MQTT in Simulation

Since Wokwi has no real WiFi, verify MQTT payload format using Serial:

```cpp
void publishMQTT(const char* topic, const char* payload) {
  Serial.print("[MQTT] Topic: "); Serial.print(topic);
  Serial.print(" | Payload: "); Serial.println(payload);
  // Real code: mqttClient.publish(topic, payload);
}

// Usage in any simulation:
publishMQTT("smarthome/kitchen/gas", "ALARM: Leak detected!");
publishMQTT("smarthome/water/tank_level", "85.5");
publishMQTT("smarthome/living/temperature", "28.3");
```

---

## Tinkercad Alternative

**URL:** https://tinkercad.com

**Pros:**
- Better 3D visualization
- Built-in Arduino Uno simulation
- Circuits can be shared

**Cons:**
- No ESP32 support (Arduino Uno/Nano only)
- Limited component library
- No ESPHome

**When to use Tinkercad:**
- Teaching beginners basic circuit concepts
- Testing simple sensor + LED circuits
- Creating visual wiring diagrams

**When to use Wokwi:**
- ESP32-specific code testing
- MQTT/WiFi logic verification
- Advanced sensor simulations

---

*End of 04_Simulation_Guide_Wokwi.md*
*Next: 05_Sensor_Actuator_Specifications.md*
