// Simulation 06 - Reed Switch Door Monitor (Security)
// Tests: door open/close detection + "left open too long" alert.
// In Wokwi: the PUSHBUTTON simulates a reed switch (press = closed/magnet).
//   Normally-open circuit: press -> pin LOW (via INPUT_PULLUP).

const int REED_PIN = 23;
const int LED_PIN = 19;

// TUNABLE
unsigned long OPEN_ALERT_DELAY = 30000;  // Alert if open >30 s

bool doorOpen = false;
unsigned long openTime = 0;

void setup() {
  Serial.begin(115200);
  pinMode(REED_PIN, INPUT_PULLUP);   // reed switch to GND
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.println("Door Monitor Sim Started");
  Serial.println("Press/release the button (magnet present = door closed)");
}

void loop() {
  // Closed (magnet present) -> switch OPEN -> pin reads HIGH via pullup
  bool closed = digitalRead(REED_PIN) == HIGH;
  bool isOpen = !closed;

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
    openTime = millis();   // reset timer to avoid spamming
  }

  delay(100);
}