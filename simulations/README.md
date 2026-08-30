# Running the SmartHome Simulations in VS Code (Wokwi extension)

> Confirmed setup: **VS Code 1.132.0** with **Wokwi vscode extension (3.7.0)** + **PlatformIO IDE extension (installed)**.

---

## ⚠️ IMPORTANT — VS Code Wokwi needs a *compiled* firmware (it does NOT auto-compile)

In the **browser** (wokwi.com), Wokwi compiles your `sketch.ino` for you. The **VS Code extension does not** — before you can run the simulator you must first **build** `sketch.ino` into a firmware file, and `wokwi.toml` tells the simulator where that firmware is.

There are **two supported ways to run these simulations in VS Code**: **PlatformIO** (recommended, added here) or **arduino-cli**.

---

## OPTION A — PlatformIO (recommended; files already added)

`wokwi.toml` and `platformio.ini` are already in each simulation folder, pointing to
`.pio/build/esp32dev/firmware.elf`.

### One-time install
- PlatformIO IDE extension is already installed. On first build it will download the ESP32 toolchain (~1 GB) automatically.

### Build (must succeed before simulating)
1. Open folder `E:\SmartHome_Prototype_Complete_Docs`
2. Open `simulations/01_pir_motion_light/sketch.ino`
3. **`Ctrl+Shift+P`** → **`PlatformIO: Build`** (or click the **✓ Build** icon in the PlatformIO toolbar at the bottom)
4. Wait for the first-time toolchain download + build. Success looks like:
   ```
   RAM:   [==        ]  22.9% (used 74876 bytes)
   Flash: [===       ]  26.3% (used 687541 bytes)
   ================== [SUCCESS] Took 32.41 seconds ==================
   ```
5. This creates `.pio/build/esp32dev/firmware.elf`.

### Run in Wokwi
1. With `sketch.ino` still the active tab → **`Ctrl+Shift+P`** → **`Wokwi: Start Simulator`**
2. Now it should open (no more "wokwi.toml not found").
3. **Click the PIR** → yellow LED ON → wait 30 s → LED OFF. Serial monitor shows the `[EVENT]` lines.

### To re-test after editing `sketch.ino`
- **`PlatformIO: Build`** again, then **`Wokwi: Restart Simulator`**.

---

## OPTION B — arduino-cli (alternative without PlatformIO)

Install Arduino CLI, then:
```bash
arduino-cli core update-index
arduino-cli core install esp32:esp32
arduino-cli compile --fqbn esp32:esp32:esp32 --output-dir build simulations/01_pir_motion_light
```
Then point `wokwi.toml` `firmware` to the built `.elf` (path depends on `--output-dir`).

---

## OPTION C — Zero-install fallback: run it in the browser right now

If you just want to *see* Simulation 1 working in ~1 minute with no toolchain:
1. Go to **https://wokwi.com** → "Start from Scratch" → **ESP32**
2. Paste the contents of `simulations/01_pir_motion_light/diagram.json` into the **Diagram** tab
3. Paste `sketch.ino` into the **Code** tab (delete the default)
4. Press **▶ Start Simulation** — it auto-compiles
5. **Click the PIR** → yellow LED → 30 s → OFF

> This is the fastest way to validate the *logic*. Use it to test before/while the VS Code toolchain downloads.

---

## Troubleshooting

| Symptom | Fix |
|---------|-----|
| "wokwi.toml configuration file not found" | Build firmware first (PlatformIO: Build), then Start Simulator. `wokwi.toml` + `diagram.json` must be in the same folder as the active `sketch.ino`. |
| `.pio` folder missing / firmware.elf not found | Run **PlatformIO: Build** once (creates `.pio/`). |
| First build very slow | Normal — ESP32 toolchain download (~1 GB), one-time. |
| Permission error on `.pio` | Close VS Code, reopen folder, build again. |
| Serial monitor empty | View → Output → **Wokwi** channel; make sure simulator tab is focused. |

---

## All 7 simulations — each in its own folder (built + validated, in git)

| # | Node / purpose | Folder |
|---|----------------|--------|
| 1 | PIR Motion Light | `01_pir_motion_light/` ✅ |
| 2 | DHT22 Temperature & Fan (hysteresis) | `02_dht22_climate/` ✅ |
| 3 | Soil Moisture & Water Pump (anti-flood + cooldown) | `03_soil_moisture_pump/` ✅ |
| 4 | Kitchen Gas Leak Detection & Alarm (fail-safe) | `04_gas_leak/` ✅ |
| 5 | Ultrasonic Tank Level + Dry-Run Protection | `05_water_tank/` ✅ |
| 6 | Reed Switch Door Monitor (security) | `06_reed_door/` ✅ |
| 7 | Stepper Motor Curtain (NODE-D1, auth pin map) | `07_stepper_curtain/` ✅ |

Each folder contains: `diagram.json`, `src/sketch.ino`, `platformio.ini`, `wokwi.toml`, `.gitignore`, `README.md`. Build (`PlatformIO: Build`) then run (`Wokwi: Start Simulator`).

## Wiring reference
See **`simulations/WIRING.md`** — ASCII wiring diagrams for every simulated node (color-coded, GPIO-exact). For AI-generated image versions of these diagrams, use `AUDIT/01_PROTOTYPE_PHOTO_MASTER_PROMPT.md` and save outputs to `photos/`.

---

*Next: use Option C (browser) to validate logic immediately, and Option A (PlatformIO) to run inside VS Code.*