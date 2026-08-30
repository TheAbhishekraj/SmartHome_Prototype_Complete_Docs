// Simulation 03 - Soil Moisture & Water Pump (Garden / NODE-A1 logic)
// Tests: soil-moisture threshold, pump ON, anti-flood max-time, cooldown.
// In Wokwi: adjust the POTENTIOMETER to simulate soil moisture
// (HIGH ADC = dry, LOW ADC = wet). The pump is a BLUE LED.

const int SOIL_PIN = 34;      // Analog input (potentiometer simulates moisture)
const int PUMP_PIN = 19;      // Relay output -> pump (simulated by LED)

// TUNABLE PARAMETERS
int DRY_THRESHOLD = 3000;     // ADC value above this = dry (0-4095 for ESP32)
int WET_THRESHOLD = 1500;     // ADC value below this = wet enough -> stop pump
unsigned long PUMP_MAX_TIME = 10000;   // Safety: max pump ON time = 10 s
unsigned long PUMP_COOLDOWN = 300000;  // Wait 5 min between watering cycles

unsigned long pumpStartTime = 0;
unsigned long lastWatering = 0;
bool pumpRunning = false;

void setup() {
  Serial.begin(115200);
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW);
  analogReadResolution(12);   // 0-4095
  Serial.println("Soil Moisture & Pump Sim Started");
  Serial.println("Adjust the potentiometer to simulate soil moisture");
}

void loop() {
  int moisture = analogRead(SOIL_PIN);
  Serial.print("Soil Moisture ADC: "); Serial.println(moisture);

  // SAFETY #1: anti-flood timer - force pump off after max time
  if (pumpRunning && (millis() - pumpStartTime > PUMP_MAX_TIME)) {
    digitalWrite(PUMP_PIN, LOW);
    pumpRunning = false;
    Serial.println("[SAFETY] Pump auto-stopped (max time exceeded)");
  }

  // Watering logic: dry + not already running + past cooldown
  if (moisture > DRY_THRESHOLD && !pumpRunning &&
      (millis() - lastWatering > PUMP_COOLDOWN)) {
    digitalWrite(PUMP_PIN, HIGH);
    pumpRunning = true;
    pumpStartTime = millis();
    lastWatering = millis();
    Serial.println("[ACTION] Pump STARTED - soil dry");
  }

  // Stop when wet enough
  if (pumpRunning && moisture < WET_THRESHOLD) {
    digitalWrite(PUMP_PIN, LOW);
    pumpRunning = false;
    Serial.println("[ACTION] Pump STOPPED - soil wet enough");
  }

  delay(1000);
}