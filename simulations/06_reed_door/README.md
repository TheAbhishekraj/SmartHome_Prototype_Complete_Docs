# Simulation 06 — Reed Switch Door Monitor (Security)

**Node target:** Door/window monitoring (front door + intrusion subsystem, F3).
**Purpose:** Prove open/close detection and "left open too long" alerting.

## Wiring
| Signal | GPIO | Part in Wokwi |
|--------|------|---------------|
| Reed switch (to GND, NC-close) | GPIO23 | pushbutton (INPUT_PULLUP) |
| Alert LED | GPIO19 | red LED |

## How to run
1. Open `simulations/06_reed_door/src/sketch.ino`
2. `Ctrl+Shift+P` → **`PlatformIO: Build`** → **`Wokwi: Start Simulator`**
3. Press/release the button (magnet present = door closed)

## What to test
- [ ] Release button (door open) → `[EVENT] Door OPENED` + red LED ON
- [ ] Leave open >30 s → `[ALERT] Door left open for >30 seconds!`
- [ ] Press button (door closed) → `[EVENT] Door CLOSED` + LED OFF

## Notes
- A real reed switch is paired with a magnet on the door/frame; use INPUT_PULLUP with the switch to GND.
- In the full system this feeds the intrusion alarm + Home Assistant door sensors.

*End of Simulation 06.*