# 05_Sensor_Actuator_Specifications.md
# SmartHome Prototype — Sensor & Actuator Datasheet Reference

**Version:** 1.0 | **Date:** August 2026

---

## Table of Contents
1. [ESP32 DevKit v1 Specifications](#1-esp32-devkit-v1-specifications)
2. [ESP8266 NodeMCU Specifications](#2-esp8266-nodemcu-specifications)
3. [ESP32-CAM Specifications](#3-esp32-cam-specifications)
4. [Temperature & Humidity Sensors](#4-temperature--humidity-sensors)
5. [Motion Sensors](#5-motion-sensors)
6. [Gas & Smoke Sensors](#6-gas--smoke-sensors)
7. [Water & Moisture Sensors](#7-water--moisture-sensors)
8. [Distance & Level Sensors](#8-distance--level-sensors)
9. [Current & Power Sensors](#9-current--power-sensors)
10. [Air Quality Sensors](#10-air-quality-sensors)
11. [mmWave Radar](#11-mmwave-radar)
12. [Relay Modules](#12-relay-modules)
13. [Motor Drivers](#13-motor-drivers)
14. [Solenoid Valves](#14-solenoid-valves)
15. [Contactors](#15-contactors)
16. [Stepper Motors & Drivers](#16-stepper-motors--drivers)
17. [Servo Motors](#17-servo-motors)
18. [Sirens & Buzzers](#18-sirens--buzzers)
19. [IR LEDs & Receivers](#19-ir-leds--receivers)
20. [Quick Reference Pinout Table](#20-quick-reference-pinout-table)

---

## 1. ESP32 DevKit v1 Specifications

| Parameter | Value |
|-----------|-------|
| **Chip** | ESP32-WROOM-32 |
| **Cores** | Dual-core Xtensa LX6 @ 240 MHz |
| **RAM** | 520 KB SRAM |
| **Flash** | 4 MB |
| **WiFi** | 802.11 b/g/n, 2.4 GHz |
| **Bluetooth** | BLE + Classic |
| **GPIO** | 34 programmable pins |
| **ADC** | 12-bit, 18 channels (GPIO 32-39 best for analog) |
| **DAC** | 2× 8-bit (GPIO 25, 26) |
| **Operating Voltage** | 3.3V logic, 5V tolerant on some pins |
| **Input Voltage** | 5V via USB, 7-12V via VIN |
| **Current per GPIO** | 40 mA max (12 mA recommended) |
| **Deep Sleep Current** | ~10 µA |
| **WiFi Current** | ~80-150 mA |
| **Price (India)** | ₹250–₹350 |

**Important Pins:**
- **GPIO 0:** Boot mode (must be HIGH for normal boot, LOW for programming)
- **GPIO 1/3:** UART0 (TX/RX) — used for Serial/USB, avoid for sensors
- **GPIO 6-11:** Connected to flash — DO NOT USE
- **GPIO 34-39:** Input-only (no internal pull-up), best for analog sensors
- **GPIO 2:** Built-in LED on most boards
- **GPIO 4:** Preferred for PWM (no PWM restrictions)
- **GPIO 5, 18, 19, 21, 22, 23:** General purpose, no restrictions
- **GPIO 25, 26:** DAC outputs

---

## 2. ESP8266 NodeMCU Specifications

| Parameter | Value |
|-----------|-------|
| **Chip** | ESP-12E module |
| **Core** | Single-core Xtensa @ 80/160 MHz |
| **RAM** | 80 KB |
| **Flash** | 4 MB |
| **WiFi** | 802.11 b/g/n, 2.4 GHz |
| **GPIO** | 17 pins (some shared) |
| **ADC** | 1× 10-bit (0-1V range, use voltage divider!) |
| **Operating Voltage** | 3.3V logic |
| **Input Voltage** | 5V via USB, 7-12V via VIN |
| **Current per GPIO** | 12 mA max |
| **Deep Sleep Current** | ~20 µA |
| **Price (India)** | ₹150–₹250 |

**Important Pins:**
- **GPIO 0:** Boot mode (FLASH button)
- **GPIO 1/3:** UART0 — Serial communication
- **GPIO 2:** Built-in LED (active LOW)
- **GPIO 15:** Must be LOW at boot
- **GPIO 16:** Deep sleep wake pin
- **A0 (ADC0):** 0-1V only! Use voltage divider for higher voltages
- **GPIO 4, 5, 12, 13, 14:** Best for general use

**When to use ESP8266 vs ESP32:**
- Use **ESP8266** for: Simple sensor nodes (1-2 sensors), cost-sensitive, no analog precision needed
- Use **ESP32** for: Camera, multiple sensors, analog sensors, motor control, safety-critical nodes

---

## 3. ESP32-CAM Specifications

| Parameter | Value |
|-----------|-------|
| **Chip** | ESP32-S + OV2640 camera |
| **Camera** | 2 MP OV2640, UXGA (1600×1200) |
| **RAM** | 520 KB (limited — camera uses significant portion) |
| **PSRAM** | 4 MB external (if equipped) |
| **WiFi** | 802.11 b/g/n |
| **SD Card** | MicroSD up to 4GB (FAT32) |
| **GPIO Available** | 10 pins (many shared with camera) |
| **Operating Voltage** | 5V input, 3.3V logic |
| **Current Draw** | 180-250 mA (streaming), 500 mA peak |
| **Price (India)** | ₹350–₹500 (with programmer) |

**Available GPIO Pins:**
- **GPIO 1, 3:** UART (programming)
- **GPIO 14, 15, 16:** Free for use
- **GPIO 4:** Flash LED (built-in)
- **GPIO 12, 13:** Free (but check PSRAM conflict)
- **GPIO 0:** Boot mode

**Programming:** Requires FTDI/USB-to-TTL adapter or dedicated programmer board. Connect GPIO 0 to GND during power-on to enter flash mode.

---

## 4. Temperature & Humidity Sensors

### DHT22 (AM2302)
| Parameter | Value |
|-----------|-------|
| **Range (Temp)** | -40°C to +80°C |
| **Accuracy (Temp)** | ±0.5°C |
| **Range (Humidity)** | 0-100% RH |
| **Accuracy (Humidity)** | ±2-5% RH |
| **Resolution** | 16-bit (0.1°C steps) |
| **Sampling** | 2 seconds minimum |
| **Voltage** | 3.3V–6V (5V recommended) |
| **Current** | 1.5 mA (measuring), 50 µA (idle) |
| **Protocol** | Single-wire digital (custom) |
| **Price** | ₹150–₹250 |
| **ESPHome Platform** | `dht` |

**Wiring:**
- Pin 1 (VCC) → 3.3V or 5V
- Pin 2 (DATA) → GPIO + 10kΩ pull-up to VCC
- Pin 3 (NC) — Not connected
- Pin 4 (GND) → GND

**Note:** DHT22 is slow (2s sampling). For faster/more accurate readings, use BME280.

### BME280
| Parameter | Value |
|-----------|-------|
| **Range (Temp)** | -40°C to +85°C |
| **Accuracy (Temp)** | ±0.5°C |
| **Range (Pressure)** | 300-1100 hPa |
| **Accuracy (Pressure)** | ±1 hPa |
| **Range (Humidity)** | 0-100% RH |
| **Accuracy (Humidity)** | ±3% RH |
| **Voltage** | 1.8V–3.6V (3.3V typical) |
| **Current** | 3.6 µA (sleep), 1.2 mA (measuring) |
| **Protocol** | I2C (default) or SPI |
| **I2C Address** | 0x76 or 0x77 (check module) |
| **Price** | ₹200–₹350 |
| **ESPHome Platform** | `bme280` |

**Wiring (I2C):**
- VCC → 3.3V
- GND → GND
- SCL → GPIO 22 (ESP32 default SCL)
- SDA → GPIO 21 (ESP32 default SDA)

### DS18B20 (Waterproof)
| Parameter | Value |
|-----------|-------|
| **Range** | -55°C to +125°C |
| **Accuracy** | ±0.5°C |
| **Resolution** | 9-12 bit configurable |
| **Voltage** | 3.0V–5.5V |
| **Protocol** | 1-Wire |
| **Price** | ₹80–₹150 |
| **ESPHome Platform** | `dallas` |

**Wiring:**
- Red → 3.3V/5V
- Black → GND
- Yellow → GPIO + 4.7kΩ pull-up to VCC

---

## 5. Motion Sensors

### HC-SR501 PIR
| Parameter | Value |
|-----------|-------|
| **Range** | 3-7 meters (adjustable) |
| **Angle** | 110°–140° |
| **Voltage** | 4.5V–20V (5V typical) |
| **Current** | 65 µA (idle), 3 mA (active) |
| **Output** | 3.3V HIGH when motion detected |
| **Delay Time** | 5 sec – 5 min (potentiometer) |
| **Sensitivity** | 3-7 meters (potentiometer) |
| **Trigger Mode** | L = non-retriggerable, H = retriggerable (jumper) |
| **Price** | ₹60–₹100 |
| **ESPHome Platform** | `gpio` binary_sensor |

**Wiring:**
- VCC → 5V
- GND → GND
- OUT → GPIO (any digital pin)

**Tuning Tips:**
- Set to "retriggerable" (H) for continuous motion detection
- Set delay to minimum (5s) — let ESPHome handle timing
- Sensitivity potentiometer: Start at mid-point, adjust based on false alarms
- Mount 2-2.5m high, facing slightly downward

### AM312 Mini PIR
| Parameter | Value |
|-----------|-------|
| **Range** | 3-5 meters |
| **Angle** | 100° |
| **Voltage** | 2.7V–12V |
| **Current** | 15 µA (ultra low power!) |
| **Output** | 3.3V HIGH |
| **Price** | ₹40–₹80 |

**Best for:** Battery-powered nodes, ESP32-CAM trigger

---

## 6. Gas & Smoke Sensors

### MQ-6 (LPG/Butane/Propane)
| Parameter | Value |
|-----------|-------|
| **Detects** | LPG, iso-butane, propane, LNG |
| **Range** | 200-10,000 ppm |
| **Sensitivity** | Adjustable via potentiometer |
| **Voltage** | 5V (heater needs 5V!) |
| **Heater Current** | ~150 mA |
| **Output** | Analog (0-5V) + Digital (TTL) |
| **Warm-up Time** | 24 hours first use, 1-2 min after power-on |
| **Price** | ₹120–₹200 |
| **ESPHome Platform** | `adc` (analog) or `gpio` (digital) |

**Wiring:**
- VCC → 5V (NOT 3.3V — heater won't work!)
- GND → GND
- A0 → GPIO 34-39 (ESP32) via voltage divider (5V→3.3V)
- D0 → GPIO (digital threshold output)

**IMPORTANT:** MQ-6 requires 24-hour burn-in for accurate readings. Place 30cm below ceiling (LPG is heavier than air? No — LPG is heavier! Place near floor? Actually: LPG is heavier than air, so place sensor 30cm ABOVE floor. Natural gas is lighter, place high.)

**Correction:**
- **LPG/Propane:** Heavier than air → place sensor 15-30cm from FLOOR
- **Natural Gas (Methane):** Lighter than air → place sensor 30cm from CEILING

### MQ-2 (Smoke/Flammable Gas)
| Parameter | Value |
|-----------|-------|
| **Detects** | Smoke, H2, LPG, CH4, CO, alcohol |
| **Range** | 300-10,000 ppm |
| **Voltage** | 5V |
| **Heater Current** | ~150 mA |
| **Output** | Analog + Digital |
| **Warm-up** | 24 hours first use |
| **Price** | ₹100–₹180 |

**Placement:** Ceiling mount, central in room

### Optical Smoke Sensor (TF0607 / OPT101 based)
| Parameter | Value |
|-----------|-------|
| **Detects** | Smoke particles via light scattering |
| **Voltage** | 5V |
| **Current** | <50 mA |
| **Output** | Analog or Digital |
| **Response** | Faster than MQ-2 |
| **Price** | ₹150–₹300 |

**Recommendation:** Use BOTH MQ-2 AND optical sensor for redundancy. MQ-2 for gas, optical for smoke.

---

## 7. Water & Moisture Sensors

### Capacitive Soil Moisture v1.2
| Parameter | Value |
|-----------|-------|
| **Type** | Capacitive (corrosion-resistant) |
| **Range** | 0-100% (volumetric water content) |
| **Output** | Analog 0-3.3V |
| **Voltage** | 3.3V–5V |
| **Current** | 5 mA |
| **Price** | ₹80–₹120 |
| **ESPHome Platform** | `adc` |

**Wiring:**
- VCC → 3.3V
- GND → GND
- AOUT → GPIO 34-39

**Calibration:**
- Dry soil: ~3500 (ESP32 ADC 12-bit)
- Wet soil: ~1500
- Submerged: ~800

### Water Leak Sensor (Rain Sensor Module)
| Parameter | Value |
|-----------|-------|
| **Type** | Conductive grid (corrodes over time) |
| **Output** | Analog + Digital |
| **Voltage** | 3.3V–5V |
| **Price** | ₹40–₹80 |

**Better Alternative:** DIY leak sensor using two stripped wires + 10kΩ pull-up. When water bridges wires, GPIO goes LOW.

### Float Switch
| Parameter | Value |
|-----------|-------|
| **Type** | Magnetic reed in PP/stainless housing |
| **Switch** | NO (Normally Open) or NC (Normally Closed) |
| **Voltage** | Max 100V (signal level) |
| **Current** | 0.5A max |
| **Price** | ₹60–₹120 |
| **ESPHome Platform** | `gpio` binary_sensor |

**Wiring:**
- One wire → GPIO + internal pull-up
- Other wire → GND
- When float rises, reed closes → GPIO pulled LOW

---

## 8. Distance & Level Sensors

### HC-SR04 Ultrasonic
| Parameter | Value |
|-----------|-------|
| **Range** | 2 cm – 400 cm |
| **Accuracy** | ±3 mm |
| **Angle** | 15° cone |
| **Voltage** | 5V (can work at 3.3V with reduced range) |
| **Current** | 15 mA |
| **Trigger Pulse** | 10 µs HIGH |
| **Echo Pulse** | Width = distance (58 µs/cm) |
| **Price** | ₹60–₹120 |
| **ESPHome Platform** | `ultrasonic` |

**Wiring:**
- VCC → 5V
- GND → GND
- TRIG → GPIO
- ECHO → GPIO (use voltage divider 5V→3.3V for ESP32!)

**Note:** ESP32 is 3.3V logic. HC-SR04 ECHO outputs 5V. Use voltage divider (1kΩ + 2kΩ) or logic level shifter.

### JSN-SR04T (Waterproof Ultrasonic)
| Parameter | Value |
|-----------|-------|
| **Range** | 25 cm – 450 cm |
| **Waterproof** | IP67 sensor head |
| **Price** | ₹250–₹400 |

**Best for:** Outdoor tank level, rain-exposed applications

---

## 9. Current & Power Sensors

### ACS712 (5A / 20A / 30A)
| Parameter | 5A Module | 20A Module | 30A Module |
|-----------|-----------|------------|------------|
| **Range** | ±5A | ±20A | ±30A |
| **Sensitivity** | 185 mV/A | 100 mV/A | 66 mV/A |
| **Voltage** | 5V | 5V | 5V |
| **Output** | 2.5V ± (sensitivity × current) | | |
| **Isolation** | 2.1 kV | 2.1 kV | 2.1 kV |
| **Price** | ₹80–₹150 | | |
| **ESPHome Platform** | `adc` with calibration | | |

**Wiring:**
- VCC → 5V
- GND → GND
- VOUT → GPIO 34-39 (ESP32) via voltage divider (5V→3.3V)
- IP+ / IP- → Series with load wire

**Calibration Formula:**
```
Voltage = (ADC / 4095) × 3.3
Current = (Voltage - 1.65) / Sensitivity
```

### PZEM-004T v3.0
| Parameter | Value |
|-----------|-------|
| **Measures** | Voltage (80-260V AC), Current (0-100A), Power, Energy, Frequency, Power Factor |
| **Voltage** | 5V (isolated from mains) |
| **Protocol** | UART (TTL) |
| **Isolation** | Optocoupler + transformer |
| **Price** | ₹550–₹750 |
| **ESPHome Platform** | `pzemac` or custom UART |

**Wiring:**
- 5V → 5V
- GND → GND
- TX → GPIO 16 (ESP32 RX)
- RX → GPIO 17 (ESP32 TX)
- CT Clamp → Around live wire (not both!)

**CRITICAL:** CT clamp goes around EITHER live OR neutral, NOT both. Arrow on clamp points toward load.

---

## 10. Air Quality Sensors

### PMS5003 (Plantower)
| Parameter | Value |
|-----------|-------|
| **Measures** | PM1.0, PM2.5, PM10 (μg/m³) |
| **Range** | 0-500 μg/m³ |
| **Voltage** | 5V (needs 500mA peak!) |
| **Protocol** | UART |
| **Price** | ₹1,000–₹1,500 |
| **ESPHome Platform** | `pmsx003` |

**Wiring:**
- VCC → 5V (dedicated supply recommended)
- GND → GND
- TX → GPIO 16
- RX → GPIO 17
- SET → 3.3V (active mode) or GND (sleep mode)
- RESET → 3.3V via 10kΩ

### MH-Z19B (CO2)
| Parameter | Value |
|-----------|-------|
| **Range** | 0-5000 ppm |
| **Accuracy** | ±50 ppm + 5% reading |
| **Voltage** | 5V |
| **Protocol** | UART or PWM |
| **Price** | ₹1,500–₹2,000 |
| **ESPHome Platform** | `mhz19` |

**Wiring:**
- VCC → 5V
- GND → GND
- TX → GPIO 16
- RX → GPIO 17

**Note:** Needs 3-minute warm-up for accurate readings. Self-calibration every 24 hours (expose to fresh air periodically).

### CCS811 (VOC/eCO2)
| Parameter | Value |
|-----------|-------|
| **Measures** | TVOC (0-1187 ppb), eCO2 (400-8192 ppm) |
| **Voltage** | 1.8V–3.3V |
| **Protocol** | I2C (0x5A or 0x5B) |
| **Price** | ₹300–₹500 |
| **ESPHome Platform** | `ccs811` |

**Wiring:**
- VCC → 3.3V
- GND → GND
- SCL → GPIO 22
- SDA → GPIO 21
- WAKE → GND (always awake)

---

## 11. mmWave Radar

### LD2410B (Hi-Link)
| Parameter | Value |
|-----------|-------|
| **Frequency** | 24 GHz |
| **Range** | 0.4–6 meters |
| **Detects** | Human presence, movement, micro-movements (breathing) |
| **Voltage** | 5V |
| **Protocol** | UART |
| **Output** | GPIO (presence) + UART (distance, energy) |
| **Price** | ₹400–₹600 |
| **ESPHome Platform** | Custom UART component or `ld2410` (if available) |

**Wiring:**
- VCC → 5V
- GND → GND
- OUT → GPIO (presence signal)
- TX → GPIO 16
- RX → GPIO 17

**Best for:** Fall detection, occupancy sensing, sleep monitoring (breathing detection)

---

## 12. Relay Modules

### 5V Single-Channel Relay
| Parameter | Value |
|-----------|-------|
| **Control Voltage** | 5V (3.3V may work but unreliable) |
| **Load Voltage** | 10A @ 250V AC or 10A @ 30V DC |
| **Isolation** | Optocoupler + diode |
| **Input Current** | ~15 mA |
| **Price** | ₹40–₹80 |
| **ESPHome Platform** | `gpio` switch |

**Wiring:**
- VCC → 5V
- GND → GND
- IN → GPIO
- COM → Load wire
- NO → Live wire (normally open)
- NC → Live wire (normally closed)

**CRITICAL:**
- Use NO (Normally Open) for safety — device is OFF when ESP32 is off
- Add snubber circuit for inductive loads (fans, motors)
- Fuse relay output appropriately

### 4-Channel Relay Module
| Parameter | Value |
|-----------|-------|
| **Channels** | 4 independent |
| **Control** | 5V per channel |
| **Price** | ₹100–₹200 |

**Note:** Most relay modules are ACTIVE LOW — GPIO LOW = relay ON. Check your module with multimeter.

---

## 13. Motor Drivers

### L298N Dual H-Bridge
| Parameter | Value |
|-----------|-------|
| **Channels** | 2 (dual motor) |
| **Voltage** | 5V–35V motor supply |
| **Current** | 2A per channel (peak 3A) |
| **Logic Voltage** | 5V (may need level shifter for 3.3V ESP32) |
| **Price** | ₹100–₹200 |

**Wiring:**
- Motor Power → 12V battery/PSU
- GND → Common GND with ESP32
- 5V → 5V (or use onboard 5V regulator)
- IN1, IN2 → GPIO (Motor A direction)
- ENA → GPIO PWM (Motor A speed)
- IN3, IN4 → GPIO (Motor B direction)
- ENB → GPIO PWM (Motor B speed)
- OUT1/2 → Motor A
- OUT3/4 → Motor B

**Note:** L298N has ~2V voltage drop. Use higher voltage supply or better driver (TB6612, DRV8833) for efficiency.

---

## 14. Solenoid Valves

### 12V DC Brass Solenoid Valve (½")
| Parameter | Value |
|-----------|-------|
| **Type** | Normally Closed (NC) |
| **Voltage** | 12V DC |
| **Current** | 0.5–1A |
| **Pressure** | 0.02-0.8 MPa (0.2-8 bar) |
| **Port** | ½" BSP (G1/2) |
| **Material** | Brass body, stainless core |
| **Price** | ₹400–₹600 |

**Wiring:**
- One wire → 12V+
- Other wire → Relay COM → Relay NO → 12V-
- When relay activates, circuit completes, valve opens

**IMPORTANT:**
- Install filter upstream (solenoids jam with debris)
- Use only for clean water/gas
- Never energize continuously for >30 minutes without cooling
- Add flyback diode across valve terminals

---

## 15. Contactors

### 25A AC Contactor (230V coil)
| Parameter | Value |
|-----------|-------|
| **Rating** | 25A @ 230V AC |
| **Coil Voltage** | 230V AC or 12V/24V DC |
| **Application** | Motor pump, geyser, AC unit |
| **Auxiliary Contacts** | 1NO + 1NC (for feedback) |
| **Mounting** | DIN rail |
| **Price** | ₹300–₹500 |

**Wiring:**
- Main contacts: Series with load (pump motor)
- Coil: Through relay → 230V supply
- AUX NO: To ESP32 GPIO (contactor status feedback)

**CRITICAL:**
- Contactor handles HIGH CURRENT — use appropriate cable gauge (2.5mm² minimum for 16A)
- Install in electrical panel only
- Must be installed by licensed electrician

---

## 16. Stepper Motors & Drivers

### 28BYJ-48 Stepper Motor
| Parameter | Value |
|-----------|-------|
| **Type** | 5-wire unipolar |
| **Steps per Rev** | 2048 (with gearbox 64:1) |
| **Voltage** | 5V–12V |
| **Current** | 240 mA per phase |
| **Torque** | ~300 g-cm |
| **Price** | ₹100–₹150 |

### A4988 Stepper Driver
| Parameter | Value |
|-----------|-------|
| **Type** | Bipolar stepper driver |
| **Voltage** | 8V–35V |
| **Current** | 1A per phase (2A with heatsink) |
| **Microstepping** | Full, 1/2, 1/4, 1/8, 1/16 |
| **Price** | ₹70–₹120 |

**Wiring:**
- VMOT → 12V
- GND → GND
- VDD → 3.3V/5V
- STEP → GPIO (pulse = step)
- DIR → GPIO (direction)
- MS1/2/3 → GND (full step) or GPIO (microstepping)
- 1A/1B/2A/2B → Motor coils

**Current Limit:** Adjust potentiometer on A4988. Measure Vref = I_limit × 0.4. For 0.5A: Vref = 0.2V.

---

## 17. Servo Motors

### SG90 Micro Servo
| Parameter | Value |
|-----------|-------|
| **Torque** | 1.8 kg-cm |
| **Voltage** | 4.8V–6V |
| **Current** | 100 mA (idle), 250 mA (moving), 500 mA+ (stall) |
| **Rotation** | 180° |
| **Control** | PWM 50Hz, 0.5-2.5ms pulse |
| **Price** | ₹60–₹100 |
| **ESPHome Platform** | `servo` |

**Wiring:**
- Brown → GND
- Red → 5V (external supply recommended for multiple servos)
- Orange → GPIO

---

## 18. Sirens & Buzzers

### 12V Piezo Electronic Siren
| Parameter | Value |
|-----------|-------|
| **Voltage** | 12V DC |
| **Current** | 200-500 mA |
| **Sound Level** | 110-120 dB |
| **Price** | ₹150–₹300 |

**Wiring:** Through relay module. DO NOT connect directly to ESP32 GPIO.

### Active Buzzer (5V)
| Parameter | Value |
|-----------|-------|
| **Voltage** | 5V |
| **Current** | 30 mA |
| **Sound Level** | 85 dB |
| **Price** | ₹20–₹50 |

**Can drive directly from ESP32 GPIO via transistor.**

---

## 19. IR LEDs & Receivers

### IR LED (940nm)
| Parameter | Value |
|-----------|-------|
| **Wavelength** | 940 nm |
| **Voltage** | 1.2V–1.5V |
| **Current** | 20-100 mA |
| **Price** | ₹5–₹15 |

**Wiring:** GPIO → 100Ω resistor → IR LED → GND

### TSOP1838 IR Receiver
| Parameter | Value |
|-----------|-------|
| **Voltage** | 2.5V–5.5V |
| **Carrier** | 38 kHz |
| **Range** | 10-15 meters |
| **Price** | ₹15–₹40 |

**Wiring:** VCC → 3.3V/5V, GND → GND, OUT → GPIO

---

## 20. Quick Reference Pinout Table

| Node Type | ESP32 GPIO Used | Notes |
|-----------|----------------|-------|
| **Basic Sensor** | 34 (analog), 23 (digital) | Input-only for analog |
| **PIR Light** | 23 (PIR), 19 (relay) | |
| **DHT22 Climate** | 21 (DHT), 19 (relay) | Pull-up on data pin |
| **BME280** | 21 (SDA), 22 (SCL) | I2C bus |
| **DS18B20** | 4 (1-Wire) | 4.7kΩ pull-up |
| **Ultrasonic** | 5 (TRIG), 18 (ECHO) | Voltage divider on ECHO |
| **MQ-6 Gas** | 34 (analog), 23 (digital) | 5V sensor, divider needed |
| **ACS712 Current** | 34 (analog) | Voltage divider |
| **PZEM-004T** | 16 (RX), 17 (TX) | UART |
| **PMS5003** | 16 (RX), 17 (TX) | UART, 5V supply |
| **MH-Z19B** | 16 (RX), 17 (TX) | UART, 5V supply |
| **Stepper Motor** | 18 (STEP), 19 (DIR) | |
| **Servo** | 13 (PWM) | 50Hz PWM |
| **IR LED** | 19 (PWM) | 38kHz carrier |
| **ESP32-CAM** | 4 (flash), 13 (PIR) | Limited free pins |
| **L298N Motor** | 18, 19 (dir), 25, 26 (PWM) | |
| **Reed Switches** | 23, 22, 21, 19 | INPUT_PULLUP |
| **Float Switches** | 23, 22 | INPUT_PULLUP |

> ⚠️ **NOTE (2026):** Rows above are *generic example* assignments for a single-sensor node. They are **NOT** all simultaneously valid on one ESP32 — e.g. **Stepper (18/19)**, **IR LED (19)** and **Reed Switches (19)** share GPIO19 and must never coexist as shown. For multi-function nodes use the **authoritative per-node pin map in File 06** (see in particular **NODE-D1**, which already resolves these conflicts: stepper on 26/27/25, IR on 17, relay on 16, reeds on 19/18).
> Hard constraints that ALWAYS apply: GPIO1/3 (UART0) and GPIO6–11 (flash) are reserved; GPIO34–39 are analog-input-only (no internal pull-up).

---

*End of 05_Sensor_Actuator_Specifications.md*
*Next: 06_ESPHome_YAML_Configurations_All_Nodes.md*
