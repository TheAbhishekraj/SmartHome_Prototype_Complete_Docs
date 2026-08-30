# Running the SmartHome Simulations in VS Code & Wokwi

> Supported setup: **VS Code** with **Wokwi VS Code extension** + **PlatformIO IDE**, or **Zero-Install Web Simulation on Wokwi.com**.

---

## ⚠️ IMPORTANT — VS Code Wokwi needs a *compiled* firmware (it does NOT auto-compile)

In the **browser** (wokwi.com), Wokwi compiles your `sketch.ino` automatically in the cloud. The **VS Code extension** requires pre-compiled firmware or PlatformIO build (`.pio/build/esp32dev/firmware.elf`), specified in `wokwi.toml`.

There are **three supported ways to run these simulations**:

---

## OPTION A — Zero-Install Web Simulation (Fastest & 100% Instant)

If you want to run any simulation in ~10 seconds with zero local setup:
1. Go to **[https://wokwi.com](https://wokwi.com)** → Click **"Start from Scratch"** → Select **ESP32**.
2. Copy the contents of the simulation folder's `diagram.json` and paste it into the **Diagram** tab.
3. Copy the contents of `src/sketch.ino` and paste it into the **Code** tab.
4. Press **▶ Start Simulation** — Wokwi auto-compiles and runs interactively.

---

## OPTION B — PlatformIO in VS Code (Local Desktop IDE)

Each simulation folder contains `wokwi.toml`, `platformio.ini`, `diagram.json`, and `src/sketch.ino`.

### Build & Run Steps:
1. Open the project root folder in VS Code.
2. Open `simulations/<folder>/src/sketch.ino`.
3. Press **`Ctrl+Shift+P`** → **`PlatformIO: Build`** (or click the **✓ Build** checkmark in the bottom status bar).
4. Once built successfully, press **`Ctrl+Shift+P`** → **`Wokwi: Start Simulator`**.
5. The interactive simulation pane will open.

---

## Complete Simulation Suite Index (11 Functional Testbeds)

| # | Node Domain & Function | Directory | Key Components & Features |
|:---:|---|---|---|
| **01** | PIR Motion Light | `01_pir_motion_light/` | PIR sensor, 30s auto-off timer, yellow status indicator. |
| **02** | DHT22 Climate Fan | `02_dht22_climate/` | DHT22 temp/humidity sensor, fan relay with hysteresis band. |
| **03** | Soil Moisture Pump | `03_soil_moisture_pump/` | Soil moisture analog sensor, pump relay, anti-flood timeout. |
| **04** | Kitchen Gas Leak Alarm | `04_gas_leak/` | MQ-6 gas sensor, emergency shutoff solenoid, alarm buzzer. |
| **05** | Water Tank Ultrasonic | `05_water_tank/` | HC-SR04 level sensor, pump relay, dry-run float protection. |
| **06** | Reed Switch Door Security | `06_reed_door/` | Magnetic reed switch, intrusion detection, perimeter alert. |
| **07** | Stepper Motor Curtain | `07_stepper_curtain/` | A4988 stepper driver, motorized curtain position control. |
| **08** | **Smart Room Fan & Light Auto-Switch** | `08_smart_room_light_fan_auto_switch/` | **PIR presence auto-off, LDR lux gating, temp-adaptive fan, 2x physical wall switch 2-way sync.** |
| **09** | **Smart Energy Monitor & Load Shedder** | `09_energy_monitor_load_shedding/` | **Real-time current (0-25A) & power (W/kWh), 16x2 I2C LCD, auto heavy-load shedding during overload.** |
| **10** | **Indoor Air Quality & Auto Exhaust** | `10_air_quality_auto_exhaust/` | **MQ-135 analog air quality, 3-stage LEDs, auto exhaust fan purge cycle with anti-chatter hysteresis.** |
| **11** | **Smart Doorbell, Panic Button & Fall** | `11_smart_doorbell_panic_fall/` | **Doorbell 2-tone melodic chime, latching emergency panic button, elder fall sensor, reset switch.** |

---

## Wiring Reference
See **`simulations/WIRING.md`** for GPIO-exact color-coded wiring references for all 11 simulated nodes.