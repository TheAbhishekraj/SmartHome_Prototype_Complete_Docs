# Simulation 01 — PIR Motion Light

**Node target:** Kitchen light (B2) / any motion-activated light.
**Purpose:** Prove the PIR → relay → light logic and adjustable OFF delay before touching hardware.

## Files
| File | What it is |
|------|-----------|
| `diagram.json` | Wokwi circuit — ESP32 + PIR + yellow LED (stands in for relay+bulb) |
| `sketch.ino` | Arduino test code (long log / logic verification) |
| `firmware/01_pir_motion_light/pir_motion_light.yaml` | Real ESPHome config for the physical node |

## Wiring (matches ESPHome + File 05 rules)
| Signal | GPIO |
|--------|------|
| PIR VCC | 3V3 |
| PIR GND | GND |
| PIR OUT | GPIO23 |
| Relay coil (LED) | GPIO19 |

> GPIO19 is fine here because this is a **single-function** node (no IR/reed sharing). On the multi-function **NODE-D1** we deliberately used a different map (see File 06).

## How to run in Wokwi
1. Open https://wokwi.com → "Start from Scratch" → ESP32.
2. Paste `diagram.json` into the Diagram tab.
3. Paste `sketch.ino` into the Code tab (rename to `sketch.ino`).
4. Start simulation → **click the PIR** and watch the LED + Serial log.

## What to test (checklist)
- [ ] Click PIR → LED ON, Serial prints `[EVENT] Motion detected -> Light ON`
- [ ] No motion for 30 s → LED OFF, prints `[EVENT] Timeout -> Light OFF`
- [ ] Re-click PIR within 30 s → timer resets, light stays ON
- [ ] Set `MOTION_TIMEOUT = 5000` → faster cycles (sanity check the timer logic)
- [ ] Toggle `TRIGGER_ON_RISING = false` → confirm behavior differences

## Bench / commissioning notes (from File 11)
- On the real breadboard, drive the relay via the module (never the ESP GPIO straight to mains).
- Verify the relay module is ACTIVE-LOW or ACTIVE-HIGH and, if needed, add `inverted: true` to the ESPHome `switch` so it matches the module — this is the #1 cause of "LED/light never turns on".
- Confirm OTA from the ESPHome dashboard (`Install → Wirelessly`) works before mounting.

*End of Simulation 01.*