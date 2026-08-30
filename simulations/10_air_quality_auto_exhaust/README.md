# Simulation 10: Indoor Air Quality & Automated Exhaust Fan

## Overview
Demonstrates automated ventilation control driven by an analog air quality / VOC / smoke sensor (MQ-135 / PMS5003). It automatically purges room air during cooking, smoke, or humidity buildup, with hysteresis to prevent relay cycling and a minimum purge timer.

---

## Hardware Components
- **ESP32 DevKit V1**
- **Potentiometer (MQ-135 Sensor Simulator: 200–2000 PPM)** on `GPIO34`
- **Relay (Exhaust Fan / Cyan LED)** on `GPIO19`
- **Clean Air LED (Green)** on `GPIO18`
- **Moderate Air LED (Yellow)** on `GPIO5`
- **Hazardous Air LED (Red)** on `GPIO17`
- **Hazard Buzzer** on `GPIO23`

---

## Operating Logic
1. **Air Quality Levels:**
   - `< 400 PPM`: Green LED ON (Clean / Good).
   - `400 – 800 PPM`: Yellow LED ON (Moderate).
   - `> 800 PPM`: Red LED ON (Poor / Hazardous).
   - `> 1400 PPM`: Buzzer pulses continuous hazard alert.
2. **Auto-Ventilation:**
   - Fan automatically switches ON when PPM reaches `600`.
   - Fan continues running until air drops below `400 PPM` AND a minimum purge time (6s in simulation, 5m in real life) has elapsed.

---

## Running in VS Code & Wokwi
- **Browser:** Open [wokwi.com](https://wokwi.com), load `diagram.json` and `src/sketch.ino`.
- **VS Code:** Run `PlatformIO: Build`, then `Wokwi: Start Simulator`.
