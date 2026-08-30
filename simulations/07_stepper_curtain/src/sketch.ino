// Simulation 07 - Stepper Motor Curtain (Living Comfort / NODE-D1)
// Tests: curtain open/close via bi-polar stepper (A4988).
// Uses the AUTHORITATIVE D1 pin map from File 06:
//   STEP=GPIO26, DIR=GPIO27, ENABLE=GPIO25.

const int STEP_PIN = 26;   // A4988 STEP
const int DIR_PIN = 27;    // A4988 DIR
const int EN_PIN  = 25;    // A4988 EN (active LOW -> drive LOW to enable)

// TUNABLE
int STEPS_PER_REV = 200;      // for NEMA17 (Wokwi stepper-motor part)
int CURTAIN_STEPS = 1600;     // full travel = 8 revs (TUNE to your curtain)
int STEP_DELAY_US = 2000;     // 500 steps/s -> adjust for smoothness

void setup() {
  Serial.begin(115200);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW);   // enable driver
  Serial.println("Curtain Motor Sim Started");
}

void moveCurtain(bool open) {
  digitalWrite(DIR_PIN, open ? HIGH : LOW);
  Serial.println(open ? "[ACTION] Opening curtain..." : "[ACTION] Closing curtain...");
  for (int i = 0; i < CURTAIN_STEPS; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(STEP_DELAY_US);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(STEP_DELAY_US);
  }
  Serial.println("[DONE] Curtain movement complete");
}

void loop() {
  moveCurtain(true);    // morning open
  delay(5000);
  moveCurtain(false);   // night close
  delay(5000);
}