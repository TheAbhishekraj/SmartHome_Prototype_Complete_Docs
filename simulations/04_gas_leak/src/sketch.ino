// Simulation 04 - Gas Leak Detection & Alarm (Kitchen / NODE-B1)
// Tests: gas threshold, noise-averaging, confirmation, FAIL-SAFE relay seq.
// In Wokwi: turn the POTENTIOMETER up to simulate a gas leak.
//   SIREN=buzzer(18)  EXHAUST=cyan LED(19)  VALVE=red LED(21)

const int GAS_PIN = 34;       // MQ-6 analog input
const int SIREN_PIN = 18;     // Buzzer / siren
const int EXHAUST_PIN = 19;   // Kitchen exhaust fan relay
const int VALVE_PIN = 21;     // Gas solenoid valve (CLOSED on HIGH)

// TUNABLE PARAMETERS (calibrate against real MQ-6 after 48h burn-in!)
int GAS_THRESHOLD = 2000;      // ADC above this = leak
unsigned long ALARM_DURATION = 60000;  // Siren max 1 minute

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
  Serial.println("Turn the potentiometer UP to simulate a gas leak");
}

void loop() {
  int gasRaw = analogRead(GAS_PIN);

  // Moving average over 10 samples to reject noise spikes
  gasReadings[readingIndex] = gasRaw;
  readingIndex = (readingIndex + 1) % 10;
  long gasAvg = 0;
  for (int i = 0; i < 10; i++) gasAvg += gasReadings[i];
  gasAvg /= 10;

  Serial.print("Gas ADC: "); Serial.print(gasRaw);
  Serial.print("  Avg: "); Serial.println(gasAvg);

  // Leak detection WITH confirmation (all 10 samples above threshold)
  if (gasAvg > GAS_THRESHOLD && !alarmActive) {
    bool confirmed = true;
    for (int i = 0; i < 10; i++) {
      if (gasReadings[i] <= GAS_THRESHOLD) { confirmed = false; break; }
    }
    if (confirmed) {
      alarmActive = true;
      alarmStartTime = millis();
      // SAFETY SEQUENCE: Exhaust ON -> Valve CLOSED -> Siren ON
      digitalWrite(EXHAUST_PIN, HIGH);
      Serial.println("[CRITICAL] Exhaust fan ON");
      delay(500);
      digitalWrite(VALVE_PIN, HIGH);      // valve closed
      Serial.println("[CRITICAL] Gas valve CLOSED");
      delay(500);
      digitalWrite(SIREN_PIN, HIGH);
      Serial.println("[CRITICAL] SIREN ACTIVATED");
      Serial.println("[ALERT] MQTT: smarthome/kitchen/gas = LEAK");
    }
  }

  // Auto-stop siren after duration; exhaust+valve STAY safe until manual reset
  if (alarmActive && (millis() - alarmStartTime > ALARM_DURATION)) {
    digitalWrite(SIREN_PIN, LOW);
    Serial.println("[INFO] Siren auto-stopped (duration expired) - safety state persists");
  }

  // Manual reset: bring pot to ~0
  if (alarmActive && gasAvg < 500) {
    alarmActive = false;
    digitalWrite(SIREN_PIN, LOW);
    digitalWrite(EXHAUST_PIN, LOW);
    digitalWrite(VALVE_PIN, LOW);   // valve OPEN
    Serial.println("[RESET] Gas cleared. System reset. Valve reopened (manual only).");
  }

  delay(500);
}