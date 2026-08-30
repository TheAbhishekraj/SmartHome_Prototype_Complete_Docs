# Simulation 07 — Stepper Motor Curtain (Living Comfort / NODE-D1)

**Node target:** Living-room curtain (part of the complex NODE-D1).
**Purpose:** Prove bi-polar stepper motor control (A4988) — the moving part of the D1 node.

## Wiring — uses the AUTHORITATIVE D1 pin map (File 06)
| Signal | GPIO |
|--------|------|
| A4988 STEP | GPIO26 |
| A4988 DIR | GPIO27 |
| A4988 EN (active LOW) | GPIO25 |
| A4988 VDD | 3V3 |
| coil pairs | 1A/1B/2A/2B → stepper |

> These pins are deliberately **different** from the generic File 05 example (which used 18/19) so that on the real multi-device D1 node the stepper **does not collide** with the IR LED (17) / relay (16) / reeds (18/19). See File 06.

## How to run
1. Open `simulations/07_stepper_curtain/src/sketch.ino`
2. `Ctrl+Shift+P` → **`PlatformIO: Build`** → **`Wokwi: Start Simulator`**
3. Watch the stepper motor rotate (open → close loop), Serial shows the phases

## What to test
- [ ] Loop alternates `Opening...` / `Closing...` every 5 s
- [ ] DIR toggles correctly (direction reverses)
- [ ] EN held LOW keeps the driver enabled
- [ ] Tune `CURTAIN_STEPS` / `STEP_DELAY_US` for your real curtain travel

## Notes (File 06 + 09)
- A4988 current limit must be set with Vref = I × 0.4 to protect the motor/driver.
- On the real node the motor rail is powered separately (12V) from the ESP logic.
- This is the ONLY actuator in the D1 cluster that needs the dedicated pin map — keep it isolated as above.

*End of Simulation 07.*