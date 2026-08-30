# Simulation 08: Smart Room Light & Fan Auto-Switch Controller

## Overview
This simulation demonstrates the complete room lighting and climate controller logic designed for residential switchboard retrofits. It integrates occupancy detection, twilight lux gating, temperature-adaptive fan automation, and seamless manual wall switch overrides with instant state synchronization.

---

## Hardware Components
- **ESP32 DevKit V1**
- **PIR Motion Sensor (HC-SR501 / AM312)** on `GPIO13`
- **LDR Light Sensor** on `GPIO34` (Analog ADC)
- **DHT22 Temperature & Humidity Sensor** on `GPIO23`
- **Relay 1 (Ceiling Light / Yellow LED)** on `GPIO19`
- **Relay 2 (Ceiling Fan / Cyan LED)** on `GPIO18`
- **Wall Switch 1 (Light Override)** on `GPIO25` (Internal Pull-Up)
- **Wall Switch 2 (Fan Override)** on `GPIO26` (Internal Pull-Up)

---

## Operating Logic
1. **Manual Wall Switch Override:** Pressing either pushbutton immediately toggles the respective light or fan relay and resets the inactivity timer.
2. **Occupancy Auto-ON:** Clicking the PIR sensor registers presence. If ambient light is dark (LDR > threshold), the light turns ON. If temperature > 28°C, the fan turns ON.
3. **Vacancy Auto-OFF:** If no motion occurs for 15 seconds (demo mode), both lights and fans automatically switch OFF to save energy.

---

## Running in VS Code & Wokwi
- **Browser:** Open [wokwi.com](https://wokwi.com), load `diagram.json` and `src/sketch.ino`.
- **VS Code:** Run `PlatformIO: Build`, then `Wokwi: Start Simulator`.
