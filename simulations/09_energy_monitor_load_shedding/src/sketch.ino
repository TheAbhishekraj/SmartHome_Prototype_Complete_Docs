/**
 * Simulation 09: Smart Energy Monitor & Automatic Load Shedder
 * Features:
 *  - Real-Time AC Current & Power Measurement (Simulated 0-25A)
 *  - I2C 16x2 LCD Display with Power & Energy Telemetry
 *  - Automated Overload Detection & Load Shedding of Heavy Appliances (AC/Geyser)
 *  - Overload Warning Buzzer & Alarm Indicator
 *  - Automatic Safe Reconnection with Cooldown Timer
 */

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define PIN_POT_CURRENT   34
#define PIN_RELAY_HEAVY   19  // AC / Water Heater Heavy Load
#define PIN_RELAY_BASE    18  // Baseline lighting load
#define PIN_BUZZER        23  // Alarm Buzzer
#define PIN_LED_ALARM     25  // Overload Warning LED

LiquidCrystal_I2C lcd(0x27, 16, 2);

const float MAINS_VOLTAGE = 230.0;        // Standard Indian Voltage (230V)
const float MAX_SAFE_CURRENT = 16.0;      // 16 Amps (3680 Watts peak limit)
const float RECOVERY_CURRENT = 12.0;      // Safe recovery threshold
const unsigned long COOLDOWN_MS = 8000;   // 8s recovery cooldown

float currentA = 0.0;
float powerW = 0.0;
float energyKWh = 0.0;
bool heavyLoadActive = true;
bool overloadState = false;
unsigned long lastUpdateTime = 0;
unsigned long overloadStartTime = 0;

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println("==================================================");
  Serial.println(" SMART ENERGY MONITOR & LOAD SHEDDER ACTIVE ");
  Serial.println(" Mains: 230V 50Hz | Max Peak Limit: 16.0A (3.68kW) ");
  Serial.println("==================================================");

  pinMode(PIN_POT_CURRENT, INPUT);
  pinMode(PIN_RELAY_HEAVY, OUTPUT);
  pinMode(PIN_RELAY_BASE, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_LED_ALARM, OUTPUT);

  // Initialize Relays ON by default
  digitalWrite(PIN_RELAY_HEAVY, HIGH);
  digitalWrite(PIN_RELAY_BASE, HIGH);
  digitalWrite(PIN_BUZZER, LOW);
  digitalWrite(PIN_LED_ALARM, LOW);

  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("SMART ENERGY HUB");
  lcd.setCursor(0, 1);
  lcd.print("SYSTEM READY...");
  delay(1500);
  lcd.clear();
}

void loop() {
  // Read Potentiometer & Calculate Current (0.0 to 25.0 Amps)
  int rawADC = analogRead(PIN_POT_CURRENT);
  currentA = (rawADC / 4095.0) * 25.0;
  powerW = currentA * MAINS_VOLTAGE;

  // Integrate Energy (kWh)
  float deltaHours = 0.5 / 3600.0;
  energyKWh += (powerW / 1000.0) * deltaHours;

  // Overload Protection Logic
  if (currentA >= MAX_SAFE_CURRENT) {
    if (!overloadState) {
      overloadState = true;
      overloadStartTime = millis();
      Serial.printf("\n[OVERLOAD CRITICAL] Current: %.2fA (Power: %.0fW) EXCEEDS 16A LIMIT!\n", currentA, powerW);
      Serial.println("[ACTION] Shedding Heavy Load Relay (AC/Geyser OFF)...");
    }

    // Shed Heavy Load
    heavyLoadActive = false;
    digitalWrite(PIN_RELAY_HEAVY, LOW);
    digitalWrite(PIN_LED_ALARM, HIGH);
    digitalWrite(PIN_BUZZER, HIGH);
  } else {
    digitalWrite(PIN_BUZZER, LOW);
    digitalWrite(PIN_LED_ALARM, LOW);

    // Auto-Recovery with Cooldown
    if (overloadState && currentA <= RECOVERY_CURRENT) {
      if (millis() - overloadStartTime >= COOLDOWN_MS) {
        overloadState = false;
        heavyLoadActive = true;
        digitalWrite(PIN_RELAY_HEAVY, HIGH);
        Serial.println("\n[RECOVERY] Power levels normalized. Heavy Load Restored.");
      }
    }
  }

  // Periodic Telemetry & LCD Refresh (every 500ms)
  if (millis() - lastUpdateTime >= 500) {
    lastUpdateTime = millis();

    // Line 1: Voltage, Current, Power
    lcd.setCursor(0, 0);
    lcd.printf("230V %.1fA %4.0fW", currentA, powerW);

    // Line 2: Heavy Load Status & Alert
    lcd.setCursor(0, 1);
    if (overloadState) {
      lcd.print("!SHED! HEAVY OFF");
    } else {
      lcd.printf("HVY:ON  E:%.2fkW", energyKWh);
    }

    Serial.printf("[METRICS] V: 230V | I: %5.2f A | P: %5.0f W | Total: %6.3f kWh | Heavy Relay: %s\n",
                  currentA, powerW, energyKWh, heavyLoadActive ? "ACTIVE" : "SHED");
  }

  delay(50);
}
