# Simulation 04 — Gas Leak Detection & Alarm (Kitchen NODE-B1) ⚠️ CRITICAL

**Node target:** Kitchen safety (B1) — gas, and its fail-safe response.
**Purpose:** Prove leak detection (with noise-averaging + confirmation) and the exact **safety relay sequence**: **Exhaust ON → Gas valve CLOSED → Siren ON**.

## Wiring
| Signal | GPIO | Part in Wokwi |
|--------|------|---------------|
| MQ-6 gas sensor (analog) | GPIO34 | potentiometer (rotate UP = leak) |
| Siren | GPIO18 | buzzer |
| Exhaust fan relay | GPIO19 | cyan LED |
| Gas solenoid valve (close on HIGH) | GPIO21 | red LED |

## How to run
1. Open `simulations/04_gas_leak/src/sketch.ino`
2. `Ctrl+Shift+P` → **`PlatformIO: Build`** → **`Wokwi: Start Simulator`**
3. Rotate the potentiometer up (leak) and watch the sequence + Serial log

## What to test (the SEQUENCE is critical)
- [ ] Increase pot slowly → 10-sample average filters noise
- [ ] Pot high for a few seconds → confirms & fires: `Exhaust ON` → `Valve CLOSED` → `SIREN ACTIVATED` (in that exact order)
- [ ] After 60 s → siren auto-stops, but **exhaust + valve stay in safe state** (no accidental re-open)
- [ ] Bring pot to 0 → manual reset: `Gas cleared. System reset.`
- [ ] **Verify the valve LED goes OFF (valve OPEN) ONLY on manual reset** — never automatically

## Safety notes (File 09)
- On real hardware the gas **valve must be new + certified**, and powered so that **power-off = valve CLOSED (fail-safe)**.
- The MQ-6 needs a **24–48 h burn-in + calibration against a known gas source**; the `GAS_THRESHOLD` (2000) is a placeholder — calibrate it on the breadboard.
- The siren/exhaust/valve are driven via **relays/modules**, never straight from a GPIO.
- A confirmed leak latches the safety state until a **human** resets — this is intentional and matches the real fail-safe requirement.

*End of Simulation 04.*