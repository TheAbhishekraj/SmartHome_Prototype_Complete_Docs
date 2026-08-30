// Simulation 01 - PIR Motion Light
// Mirrors the real ESPHome logic: motion turns a light ON,
// no motion for MOTION_TIMEOUT turns it OFF.
// In Wokwi the light is a YELLOW LED that stands in for the real relay+bulb.

const int PIR_PIN = 23;      // GPIO23 -> PIR OUT
const int RELAY_PIN = 19;    // GPIO19 -> relay coil (simulated by LED)

// TUNABLE PARAMETERS
int MOTION_TIMEOUT = 30000;    // Light stays ON this long after last motion (ms)
bool TRIGGER_ON_RISING = true; // true = fire on motion start only

unsigned long lastMotionTime = 0;
bool lightOn = false;

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  Serial.println("PIR Motion Light Sim Started");
  Serial.println("Click the PIR sensor in Wokwi to simulate motion");
  Serial.print("Motion timeout = "); Serial.println(MOTION_TIMEOUT);
}

void loop() {
  int motion = digitalRead(PIR_PIN);

  // Rising-edge trigger (optional): only react to motion START when enabled
  if (TRIGGER_ON_RISING) {
    static int prev = LOW;
    if (motion == HIGH && prev == LOW) {
      lastMotionTime = millis();
      if (!lightOn) {
        digitalWrite(RELAY_PIN, HIGH);
        lightOn = true;
        Serial.println("[EVENT] Motion detected -> Light ON");
      }
    }
    prev = motion;
  } else {
    if (motion == HIGH) {
      lastMotionTime = millis();
      if (!lightOn) {
        digitalWrite(RELAY_PIN, HIGH);
        lightOn = true;
        Serial.println("[EVENT] Motion detected -> Light ON");
      }
    }
  }

  if (lightOn && (millis() - lastMotionTime > MOTION_TIMEOUT)) {
    digitalWrite(RELAY_PIN, LOW);
    lightOn = false;
    Serial.println("[EVENT] Timeout -> Light OFF");
  }

  delay(100);
}