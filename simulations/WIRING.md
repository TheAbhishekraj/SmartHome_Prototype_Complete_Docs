# Wiring Diagram Reference — All Simulated Nodes

This file gives a clear, printer-friendly wiring reference for every simulated node.
**Color code:** Red = VCC/+, Black = GND, Blue/Green/Yellow/Orange/Magenta/Cyan = signal. All signals are ESP32 GPIO.

> ⚠️ These are **low-voltage ESP wiring diagrams** for simulation/bench. Mains (230V) side of relays/contactors is NOT shown — follow File 09 & File 18 for mains work and it must be wired with appropriate safety precautions.

---

## Sim 01 — PIR Motion Light (NODE-B2 / any motion light)
```
            ESP32 DevKitC V1
         ┌─────────────────────┐
         │  3V3 o──── Red ───────────────► PIR  VCC
         │  GND o──── Black ─────────────► PIR  GND
         │  GPIO23 o── Blue ─────────────► PIR  OUT
         │  GPIO19 o── Green ────────────► LED/Relay + (via/without series R)
         │  GND o──── Black ─────────────► LED/Relay −  (through 220Ω to GND)
         └─────────────────────┘
   PIR: [VCC][OUT][GND]
   Relay module is driven from GPIO19 (check ACTIVE-LOW/HIGH for `inverted:`).
```

## Sim 02 — DHT22 Climate (Living/Dining fan)
```
         │  3V3 o──── Red ───────────────► DHT22 VCC
         │  GND o──── Black ─────────────► DHT22 GND
         │  GPIO21 o── Blue ─────────────► DHT22 DATA  (+ 5-10kΩ pull-up to 3V3)
         │  GPIO19 o── Green ────────────► Fan relay
         └─────────────────────┘
```

## Sim 03 — Soil Moisture & Water Pump (Garden NODE-A1)
```
         │  3V3 o──── Red ───────────────► Soil-moisture module VCC
         │  GND o──── Black ─────────────► Soil module GND
         │  GPIO34 o── Blue ─────────────► Soil module AO (analog, input-only pin)
         │  GPIO19 o── Green ────────────► Pump contactor coil (via relay)
         └─────────────────────┘
```

## Sim 04 — Gas Leak Detection (Kitchen NODE-B1) ⚠️ CRITICAL
```
         │  3V3 o──── Red ───────────────► MQ-6 module VCC
         │  GND o──── Black ─────────────► MQ-6 GND
         │  GPIO34 o── Blue ─────────────► MQ-6 AO  (use divider, 5V sensor)
         │  GPIO18 o── Green ────────────► Siren module  (via relay)
         │  GPIO19 o── Yellow ───────────► Exhaust-fan relay
         │  GPIO21 o── Orange ───────────► Gas valve solenoid control (via relay)
         └─────────────────────┘
   Safety sequence: Exhaust ON -> Valve CLOSED -> Siren ON.
   FAIL-SAFE: power off = valve closed. Certified valve + licensed install only.
```

## Sim 05 — Ultrasonic Tank Level + Dry-Run (Water NODE-C1)
```
         │  GPIO5 o── Blue ─────────────► HC-SR04 TRIG
         │  GPIO18 o── Green ───────────► HC-SR04 ECHO (add divider if 5V)
         │  3V3  o── Red ───────────────► HC-SR04 VCC
         │  GND  o── Black ─────────────► HC-SR04 GND
         │  GPIO34 o── Orange ──────────► Pump-current sensor (ACS712 out)
         │  GPIO19 o── Green ───────────► Pump contactor coil (via relay)
         │  GPIO21 o── Red ─────────────► Dry-run alert LED / buzzer
         └─────────────────────┘
```

## Sim 06 — Reed Switch Door Monitor (Security F3)
```
         │  3V3 o──── Red ───────────────► Reed switch terminal 1
         │  GPIO23 o── Green (INPUT_PULLUP) ◄── Reed terminal 2
         │  GPIO19 o── Yellow ───────────► Alert LED / buzzer
         └─────────────────────┘
```

## Sim 07 — Stepper Curtain (Living NODE-D1) — uses AUTHORITATIVE D1 pin map
```
         A4988 driver
         ┌───────────────┐
   GPIO26 o─ Blue ──►STEP │
   GPIO27 o─ Green ─►DIR  │      coil pairs to 28BYJ-48/NEMA17:
   GPIO25 o─ Red  ─►EN   │       1A/1B  -> B+/B-
   3V3    o─ Red  ─►VDD   │       2A/2B  -> A-/A+
   GND    o─ Black ─►GND  │
         └───────────────┘   VMOT = 12V (separate supply, common GND with ESP)
   IMPORTANT: on the real D1 node the stepper uses 26/27/25 so it does NOT
   collide with IR LED (17), relay (16) or reeds (18/19). See File 06.
```

## Sim 08 — Smart Room Auto Fan & Light Controller (NODE-D1/D2/D3/D4) 🌟
```
         │  3V3 o──── Red ───────────────► PIR VCC & LDR VCC & DHT22 VCC
         │  GND o──── Black ─────────────► All Module GNDs
         │  GPIO13 o── Green ────────────► PIR Motion OUT
         │  GPIO34 o── Orange ───────────► LDR Lux AO (ADC Input)
         │  GPIO23 o── Magenta ──────────► DHT22 SDA Data
         │  GPIO19 o── Yellow ───────────► Ceiling Light Relay Module
         │  GPIO18 o── Cyan ─────────────► Ceiling Fan Relay Module (+ RC Snubber)
         │  GPIO25 o── Orange ───────────► Wall Rocker Switch 1 (to GND)
         │  GPIO26 o── Blue ─────────────► Wall Rocker Switch 2 (to GND)
         └─────────────────────┘
   Features: Real-time 2-way manual wall switch toggle sync + Occupancy auto-off + Twilight lux gating + Temperature adaptive fan.
```

## Sim 09 — Smart Energy Monitor & Load Shedder (NODE-E1 Whole-House) ⚡
```
         │  3V3 o──── Red ───────────────► Potentiometer VCC (Current sensor)
         │  GND o──── Black ─────────────► Potentiometer & Buzzer & LCD GND
         │  GPIO34 o── Orange ───────────► Current Sensor Analog In (0-25A)
         │  GPIO21 o── Magenta ──────────► LCD1602 I2C SDA
         │  GPIO22 o── Cyan ─────────────► LCD1602 I2C SCL
         │  GPIO19 o── Green ────────────► Heavy Load Relay (AC/Geyser)
         │  GPIO18 o── Yellow ───────────► Baseline Load Relay (Lights/Fans)
         │  GPIO23 o── Purple ───────────► Overload Warning Buzzer
         │  GPIO25 o── Red ──────────────► Overload Alarm Strobe LED
         └─────────────────────┘
   Features: 230V power calculation, kWh energy metering, automatic heavy-load shedding during demand spikes.
```

## Sim 10 — Indoor Air Quality & Automated Exhaust Fan (NODE-B1 Kitchen/Washroom) 💨
```
         │  3V3 o──── Red ───────────────► MQ-135 Gas Sensor VCC
         │  GND o──── Black ─────────────► MQ-135 & LEDs & Buzzer GND
         │  GPIO34 o── Orange ───────────► MQ-135 AO (Analog PPM)
         │  GPIO19 o── Cyan ─────────────► Exhaust Fan Relay Module
         │  GPIO18 o── Green ────────────► Good Air Status LED (<400 PPM)
         │  GPIO5  o── Yellow ───────────► Moderate Air Status LED (400-800 PPM)
         │  GPIO17 o── Red ──────────────► Hazardous Air Status LED (>800 PPM)
         │  GPIO23 o── Purple ───────────► Hazard Siren Buzzer (>1400 PPM)
         └─────────────────────┘
   Features: Automatic exhaust ventilation purge cycle with anti-chatter hysteresis.
```

## Sim 11 — Smart Doorbell, Panic Button & Fall Alarm (NODE-F1 / F4 / F5) 🚨
```
         │  3V3 o──── Red ───────────────► Resistors / Pull-Ups
         │  GND o──── Black ─────────────► Switch Terminals & Buzzer/LED GNDs
         │  GPIO13 o── Blue ─────────────► Outdoor Doorbell Pushbutton (to GND)
         │  GPIO14 o── Red ──────────────► Bedside/Bathroom Panic Button (to GND)
         │  GPIO27 o── Yellow ───────────► Elder Fall / Tilt Sensor (to GND)
         │  GPIO26 o── Green ────────────► Alarm Reset / Disarm Switch (to GND)
         │  GPIO19 o── Blue ─────────────► Visitor Doorbell Indicator LED
         │  GPIO18 o── Red ──────────────► Emergency Panic Strobe LED
         │  GPIO23 o── Purple ───────────► 2-Tone Melodic Chime & Piercing Siren Buzzer
         └─────────────────────┘
   Features: Melodic visitor chime + Latching critical emergency alarm with local master reset.
```

---

## Shared rules for every node
1. **Common header** (File 06 §1) — `esphome:`, `esp32:`, `logger:`, `api:`, `ota:`, `wifi:` — is required on the real node, not just sensors.
2. **Never drive a relay, siren, valve or motor from a raw GPIO** — always via a relay module (and a contactor for loads >10 A, File 09).
3. **Safety-critical devices (gas valve, water valve, mains contactors) must be new + certified** and fail-safe (power-off = safe/closed).
4. **Inductive Snubbers:** Always install an RC snubber across relay contacts switching AC motors, ceiling fans, or water pumps.
5. Analog input: use GPIO34–39 (ADC-only, no pull-ups). Reserved: GPIO1/3 (UART0), GPIO6–11 (flash).
6. Ground must be common between ESP, modules, and load supplies.

*End of Wiring Diagram Reference.*