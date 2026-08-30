// Simulation 05 - Ultrasonic Tank Level + Dry-Run Protection (Water NODE-C1)
// Tests: tank level %, pump on/off, and CRITICAL dry-run protection.
// In Wokwi: move the HC-SR04 distance to change tank level,
// and the POTENTIOMETER simulates pump motor current.

const int TRIG_PIN = 5;
const int ECHO_PIN = 18;
const int PUMP_PIN = 19;
const int ALERT_PIN = 21;
const int CURRENT_PIN = 34;  // Pump current, simulated by potentiometer

// TUNABLE PARAMETERS
float TANK_HEIGHT_CM = 100.0;   // total tank height
float PUMP_ON_LEVEL = 80.0;     // start pump when below this %
float PUMP_OFF_LEVEL = 95.0;    // stop pump when reaching this %
int DRY_RUN_CURRENT = 500;      // ADC below this during run = dry run
unsigned long DRY_RUN_TIME = 5000; // check current 5 s after pump start

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
  digitalWrite(PUMP_PIN, LOW);
  digitalWrite(ALERT_PIN, LOW);
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

  // DRY-RUN PROTECTION: if pump runs but current is too low, STOP + latch
  if (pumpRunning && (millis() - pumpStartTime > DRY_RUN_TIME)) {
    if (currentRaw < DRY_RUN_CURRENT) {
      digitalWrite(PUMP_PIN, LOW);
      pumpRunning = false;
      dryRunDetected = true;
      digitalWrite(ALERT_PIN, HIGH);
      Serial.println("[CRITICAL] DRY RUN DETECTED! Pump STOPPED.");
      Serial.println("[ALERT] MQTT: smarthome/water/dry_run = true");
    }
  }

  // Normal pump control (disabled after dry-run latching)
  if (!dryRunDetected && levelPercent < PUMP_ON_LEVEL && !pumpRunning) {
    digitalWrite(PUMP_PIN, HIGH);
    pumpRunning = true;
    pumpStartTime = millis();
    Serial.println("[ACTION] Pump STARTED - tank low");
  }

  if (pumpRunning && levelPercent >= PUMP_OFF_LEVEL) {
    digitalWrite(PUMP_PIN, LOW);
    pumpRunning = false;
    Serial.println("[ACTION] Pump STOPPED - tank full");
  }

  delay(1000);
}