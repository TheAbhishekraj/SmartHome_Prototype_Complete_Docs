# Wiring Diagram Reference — All Simulated Nodes

This file gives a clear, printer-friendly wiring reference for every simulated node.
**Color code:** Red = VCC/+, Black = GND, Blue/Green/Yellow = signal. All signals are ESP32 GPIO.

> ⚠️ These are **low-voltage ESP wiring diagrams** for simulation/bench. Mains (230V) side of relays/contactors is NOT shown — follow File 09 for mains work and it must be wired by a licensed electrician.

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

---

## Shared rules for every node
1. **Common header** (File 06 §1) — `esphome:`, `esp32:`, `logger:`, `api:`, `ota:`, `wifi:` — is required on the real node, not just sensors.
2. **Never drive a relay, siren, valve or motor from a raw GPIO** — always via a relay module (and a contactor for loads >10 A, File 09).
3. **Safety-critical devices (gas valve, water valve, mains contactors) must be new + certified** and fail-safe (power-off = safe/closed).
4. Analog input: use GPIO34–39 (ADC-only, no pull-ups). Reserved: GPIO1/3 (UART0), GPIO6–11 (flash).
5. Ground must be common between ESP, modules, and load supplies.

*End of Wiring Diagram Reference.*