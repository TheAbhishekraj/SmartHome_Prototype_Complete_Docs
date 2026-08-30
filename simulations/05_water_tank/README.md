# Simulation 05 — Ultrasonic Tank Level + Dry-Run Protection (Water NODE-C1)

**Node target:** Water tank / pump (C1) — auto-fill + **dry-run protection**.
**Purpose:** Prove level percentage, pump on/off thresholds, and the critical dry-run latch (pump must NEVER run dry).

## Wiring
| Signal | GPIO | Part in Wokwi |
|--------|------|---------------|
| HC-SR04 TRIG | GPIO5 | ultrasonic distance (→ tank level) |
| HC-SR04 ECHO | GPIO18 | ultrasonic |
| Pump current (analog) | GPIO34 | potentiometer (down = dry run) |
| Pump relay | GPIO19 | blue LED |
| Dry-run alert | GPIO21 | red LED |

## How to run
1. Open `simulations/05_water_tank/src/sketch.ino`
2. `Ctrl+Shift+P` → **`PlatformIO: Build`** → **`Wokwi: Start Simulator`**
3. Move the ultrasonic distance (tank level) and the current pot

## What to test (dry-run is the critical one)
- [ ] Large distance (empty tank, level < 80%) → pump starts
- [ ] Small distance (level ≥ 95%) → pump stops
- [ ] **5 s after pump start, drop the current pot low** → `[CRITICAL] DRY RUN DETECTED! Pump STOPPED` + red alert LED
- [ ] **Verify pump does NOT auto-restart** after dry-run (it's latched until a manual reset — by design)

## Why dry-run protection matters (File 09 water safety)
- Running a pump with no water (dry) overheats and can destroy the motor / cause a fire.
- The dry-run condition **latches** — it never silently re-starts the pump. On the real node this maps to a manual reset / HA clear.
- On hardware the pump is driven through a **contactor** sized for its stalled current, and power-off = pump off (fail-safe).

*End of Simulation 05.*