# Simulation 02 — DHT22 Temperature & Fan Control

**Node target:** Living/Dining climate control (NODE-D1 temp part) + any room fan.
**Purpose:** Prove temperature/humidity thresholds, **hysteresis**, and fan switching logic before hardware.

## Files
| File | What it is |
|------|-----------|
| `diagram.json` | Wokwi circuit — ESP32 + DHT22 + green LED (stands in for the fan relay) |
| `src/sketch.ino` | Arduino logic test |
| `platformio.ini` | Build config (adds the DHT + Adafruit Unified Sensor libraries) |
| `wokwi.toml` | Tells VS Code Wokwi where the compiled firmware is |
| `firmware/../*.yaml` | Production ESPHome config (to add when we write the real node) |

## Wiring
| Signal | GPIO |
|--------|------|
| DHT22 VCC | 3V3 |
| DHT22 GND | GND |
| DHT22 SDA/data | GPIO21 (add pull-up) |
| Fan relay (LED) | GPIO19 |

## How to run in VS Code (same as Sim 01)
1. Open folder `E:\SmartHome_Prototype_Complete_Docs`
2. Open `simulations/02_dht22_climate/src/sketch.ino`
3. `Ctrl+Shift+P` → **`PlatformIO: Build`** (first build downloads the two libraries)
4. `Ctrl+Shift+P` → **`Wokwi: Start Simulator`**
5. Click the DHT22 in the simulator → set temperature/humidity → watch the green "fan" LED + Serial log

## What to test (hysteresis is the key point)
- [ ] Set temp to **30°C** → fan LED ON, prints `[ACTION] Fan ON`
- [ ] Drop temp to **27°C** → fan **stays ON** (above TEMP_OFF=26 → hysteresis gap)
- [ ] Drop temp to **25°C** → fan OFF
- [ ] Set humidity to **75%** → fan ON regardless of temp
- [ ] Set humidity to **60%** + temp **25°C** → fan OFF

## Why hysteresis matters
If you used a single threshold (e.g. 27°C) with no dead-band, a fan at the threshold would rapidly oscillate on/off. TEMP_ON=28 / TEMP_OFF=26 gives a **2°C dead-band**, which is exactly the behaviour you want in a real room.

*End of Simulation 02.*