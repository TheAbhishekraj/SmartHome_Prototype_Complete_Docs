// Simulation 02 - DHT22 Temperature & Fan Control
// Tests: temperature/humidity thresholds, hysteresis, fan control.
// In Wokwi the fan is a GREEN LED; click the DHT22 to set temp/humidity.

#include <DHT.h>

#define DHT_PIN 21
#define FAN_PIN 19
#define DHT_TYPE DHT22

// TUNABLE THRESHOLDS
float TEMP_ON = 28.0;      // Turn fan ON above this (deg C)
float TEMP_OFF = 26.0;     // Turn fan OFF below this (deg C)
float HUMIDITY_MAX = 70.0; // Turn fan ON if humidity > this (%)
int READ_INTERVAL = 5000;  // Read sensor every 5 seconds

DHT dht(DHT_PIN, DHT_TYPE);
bool fanRunning = false;

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);
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
  Serial.print(" C  Humidity: "); Serial.print(hum); Serial.println(" %");

  // Hysteresis logic: ON at >= TEMP_ON, OFF at <= TEMP_OFF
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