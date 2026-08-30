# Simulation 11: Smart Doorbell, Panic Button & Fall Detection Alarm

## Overview
Demonstrates perimeter and personal safety monitoring, including front door visitor notification, instant latching emergency panic alerts, and elder fall detection with local audible siren and master disarm reset switch.

---

## Hardware Components
- **ESP32 DevKit V1**
- **Doorbell Pushbutton (Blue)** on `GPIO13` (Pull-Up)
- **Emergency Panic Pushbutton (Red)** on `GPIO14` (Pull-Up)
- **Fall Sensor Pushbutton (Yellow)** on `GPIO27` (Pull-Up)
- **Alarm Reset Pushbutton (Green)** on `GPIO26` (Pull-Up)
- **Visitor Indicator LED (Blue)** on `GPIO19`
- **Emergency Strobe LED (Red)** on `GPIO18`
- **Chime & Alarm Siren Buzzer** on `GPIO23`

---

## Operating Logic
1. **Visitor Doorbell:** Pressing the Blue doorbell button plays a 2-tone melodic chime for 3 seconds and illuminates the blue indicator LED.
2. **Emergency Panic / Fall:** Pressing the Red Panic button or Yellow Fall sensor triggers an **immediate, latched emergency alarm** (rapid strobe LED + piercing alarm siren).
3. **Master Reset:** Pressing the Green Reset button acknowledges and disarms the emergency alarm.

---

## Running in VS Code & Wokwi
- **Browser:** Open [wokwi.com](https://wokwi.com), load `diagram.json` and `src/sketch.ino`.
- **VS Code:** Run `PlatformIO: Build`, then `Wokwi: Start Simulator`.
