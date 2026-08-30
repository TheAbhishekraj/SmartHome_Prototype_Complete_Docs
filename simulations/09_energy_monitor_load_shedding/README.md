# Simulation 09: Smart Energy Monitor & Automatic Load Shedder

## Overview
Simulates whole-home power monitoring and automatic peak-load management (load shedding) based on PZEM-004T / CT current clamps. Prevents tripping the main utility circuit breaker when heavy appliances (AC, geyser, microwave) are run simultaneously.

---

## Hardware Components
- **ESP32 DevKit V1**
- **Potentiometer (Current Load Simulation: 0–25 Amps)** on `GPIO34`
- **I2C 16x2 LCD Display** on `GPIO21 (SDA)` / `GPIO22 (SCL)`
- **Relay 1 (Heavy Load: AC/Geyser / Green LED)** on `GPIO19`
- **Relay 2 (Base Load: Lights / Yellow LED)** on `GPIO18`
- **Buzzer** on `GPIO23`
- **Overload Warning LED (Red)** on `GPIO25`

---

## Operating Logic
1. **Normal State:** Heavy Load and Base Load relays are ON. Real-time voltage, current, wattage, and accumulated kWh are displayed on the LCD.
2. **Overload Condition:** When simulated current exceeds `16.0 A` (> 3680 Watts), the system immediately triggers the warning buzzer, turns on the red alarm LED, and **sheds the Heavy Load Relay** (AC/Geyser turns OFF).
3. **Automatic Recovery:** Once current drops below `12.0 A` and an 8-second safety cooldown completes, the Heavy Load is automatically re-energized.

---

## Running in VS Code & Wokwi
- **Browser:** Open [wokwi.com](https://wokwi.com), load `diagram.json` and `src/sketch.ino`.
- **VS Code:** Run `PlatformIO: Build`, then `Wokwi: Start Simulator`.
