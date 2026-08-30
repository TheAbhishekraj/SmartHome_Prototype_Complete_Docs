# Running the SmartHome Simulations in VS Code (Wokwi Extension)

> Confirmed setup: **VS Code 1.132.0** with the **Wokwi VSCode extension (wokwi.wokwi-vscode@3.7.0)**. This extension runs the simulator locally in a VS Code tab — no separate browser + no manual CLI install needed.

---

## 1. How the extension works (what's in each simulation folder)

Each simulation lives in its own folder, e.g. `simulations/01_pir_motion_light/`:

| File | Role in VS Code Wokwi |
|------|-----------------------|
| `sketch.ino` | The Arduino program the extension compiles & runs |
| `diagram.json` | The virtual circuit (parts + wires) the simulator renders |
| `firmware/.../*.yaml` | The *production* ESPHome config (for the real hardware, NOT used by Wokwi) |

**Wokwi (the VS Code sim) only uses `sketch.ino` + `diagram.json`.** The ESPHome YAML is your reference for what the real node will do — treat the `.ino` as the "logic test" and the YAML as the "final firmware".

---

## 2. Run Simulation 1 — step by step

1. **Open the project in VS Code**
   - File → Open Folder → select `E:\SmartHome_Prototype_Complete_Docs`
   - In the Explorer, expand `simulations/01_pir_motion_light/`
   - **Click `sketch.ino` to focus it** (important — Wokwi runs the project of the active `.ino`).

2. **Start the simulator**
   - Press `Ctrl+Shift+P` (Command Palette) → type **`Wokwi: Start Simulator`** → Enter.
   - (Menu alternative: right-click `sketch.ino` → "Open with Wokwi" in some versions.)

3. **First launch — let it download**
   - On the very first run the extension downloads the ESP32 simulation binaries (~200–400 MB). Wait for the status bar / output to show it's ready. You need internet for this one-time step only.

4. **The simulator opens** in a new tab showing the ESP32 + PIR sensor + yellow LED, wired exactly like `diagram.json`.

5. **Interact**
   - **Click the PIR sensor** in the simulator → watch the yellow LED light up.
   - The **Serial Monitor** panel opens automatically and shows the `Serial.println()` logs:
     ```
     PIR Motion Light Sim Started
     [EVENT] Motion detected -> Light ON
     ```
   - Wait 30 s with no click → LED turns OFF, logs `[EVENT] Timeout -> Light OFF`.

6. **Stop**
   - `Ctrl+Shift+P` → **`Wokwi: Stop Simulator`**.

---

## 3. Editing to test different behaviour

Inside `sketch.ino` in VS Code:

| Change | Effect |
|--------|--------|
| `MOTION_TIMEOUT = 30000` → `5000` | Light only holds 5 s instead of 30 s |
| `TRIGGER_ON_RISING = false` | Light reacts to any motion level, not just the rising edge |

Edit → **Stop Simulator** → **Start Simulator** again to apply.

---

## 4. Troubleshooting (most common issues)

| Symptom | Fix |
|---------|-----|
| "Board not supported / unknown part" | Make sure `diagram.json` is in the **same folder** as the active `sketch.ino`, and the board is `board-esp32-devkit-c-v4`. |
| Simulator window is blank / stuck | First run download not finished — wait (status bar shows progress). |
| LED never lights when clicking PIR | Check wire colors in `diagram.json`: `pir:OUT`→`esp:23`, `light:A`→`esp:19`. Also confirm the *right* `sketch.ino` is the active tab. |
| No Serial Monitor | View → Output, and pick the **Wokwi** channel in the dropdown. |
| Extension asks for "project" | Every simulation folder is its own project — open/focus its `sketch.ino` first. |
| Simulator says "make sure file is a directory with diagram.json" | The active editor must be inside a folder that has `diagram.json`. Focus the correct `sketch.ino`. |

---

## 5. How this maps to the real hardware (very important)

Wokwi proves the **logic** only. When you move to breadboard + real ESP32:

1. Don't run mains from a GPIO — use the relay module, or a contactor for >10 A (File 09).
2. Check the relay module is **ACTIVE-LOW or ACTIVE-HIGH**, and set `inverted: true` in the ESPHome YAML if needed.
3. Flash with ESPHome (`firmware/01_pir_motion_light/pir_motion_light.yaml`) via the ESPHome dashboard — use the **ESPHome YAML**, not the `.ino`.
4. The `.ino` and the YAML implement the **same behaviour**, so a passing simulation strongly predicts a working physical node.

---

## 6. One simulation at a time (our plan)

We commit each simulation to git as we finish:
1. ✅ PIR Motion Light (done) — `simulations/01_pir_motion_light/`
2. ⏭️ DHT22 Temperature & Fan Control — `simulations/02_dht22_climate/`
3. ⏭️ Water Tank / Ultrasonic level — `simulations/03_water_tank/`
4. ⏭️ Kitchen gas-leak logic — `simulations/04_gas_leak/`
5. ⏭️ Fire / smoke detection — `simulations/05_fire_detection/`
6. ⏭️ Intrusion alarm / panic — `simulations/06_alert/`
7. ⏭️ Living Room Comfort (D1 — the complex multi-device node) — `simulations/07_d1_living/`

---

*Next: open VS Code, focus `simulations/01_pir_motion_light/sketch.ino`, and press `Ctrl+Shift+P` → `Wokwi: Start Simulator`. Tell me what you see!*