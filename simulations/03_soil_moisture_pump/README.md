# Simulation 03 — Soil Moisture & Water Pump (Garden NODE-A1)

**Node target:** Garden controller (A1) — auto-watering + pump safety.
**Purpose:** Prove soil-moisture threshold, pump on/off, **anti-flood max-time** and **cooldown** without risking a real pump or flooding.

## Files
| File | What it is |
|------|-----------|
| `diagram.json` | Wokwi circuit — ESP32 + potentiometer (as soil) + blue LED (as pump) + HC-SR04 (present, unused in code) |
| `src/sketch.ino` | Arduino logic test |
| `platformio.ini` / `wokwi.toml` | Build + simulator config |

## Wiring
| Signal | GPIO |
|--------|------|
| Soil moisture (potentiometer) SIG | GPIO34 (analog input-only) |
| Pump relay (blue LED) | GPIO19 |

## How to run
1. Open `simulations/03_soil_moisture_pump/src/sketch.ino`
2. `Ctrl+Shift+P` → **`PlatformIO: Build`** → **`Wokwi: Start Simulator`**
3. **Adjust the potentiometer** to simulate soil moisture and watch the pump LED + Serial log

## What to test (the safety logic is the point)
- [ ] Pot up (dry, ADC > 3000) → pump LED ON: `[ACTION] Pump STARTED`
- [ ] Leave a little longer than **10 s** → pump **auto-stops**: `[SAFETY] Pump auto-stopped`
- [ ] Right after it stops, set pot dry again → pump **does NOT restart** (cooldown `[ACTION]` won't fire for 5 min)
- [ ] Pot down (wet, ADC < 1500) while running → pump stops: `Pump STOPPED - soil wet enough`

## Why these protections matter (File 09 water safety)
- **Anti-flood timer:** if a moisture sensor fails or the soil never "absorbs", the pump can't run forever and flood the balcony.
- **Cooldown:** prevents rapid on/off cycling that wears out the contactor/valve.
- On real hardware the pump is driven via a **contactor** (not the ESP pin) and power-off = pump off (fail-safe).

*End of Simulation 03.*