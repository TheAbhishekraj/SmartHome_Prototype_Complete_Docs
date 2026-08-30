# 📸 MASTER PROMPT — SMART-HOME PROTOTYPE PHOTO / RENDER GENERATOR

Use this file to generate highly specific, build-accurate images (blueprint renders, wiring diagrams, and finished-node photos) of each SmartHome node **before you buy or build**.

> 🔧 **How to use:** Copy the "GLOBAL STYLE BLOCK" into ANY AI image generator (Midjourney, DALL·E, Stable Diffusion, Leonardo, Ideogram, or a local SDXL/GPT-4o image model). Then append ONE node block below. Keep every value that matches what you'll actually buy so the render becomes a true build reference.

---

## 🌍 GLOBAL STYLE BLOCK (paste at the start of every prompt)

```
Photorealistic professional product photograph, soft even studio lighting,
clean light-grey background, 85mm lens, shallow depth of field.
Electronics hobbyist benchtop style, crisp details, solder joints visible,
breadboard and jumper wires, proper wire color coding
(red=+5V, black=GND, green=signal), printed circuit, ESP32 DevKit V1 board
with gold antenna area, tidy cable management, IP65 ABS enclosure,
small black 2-channel relay module, label with a white rectangle.
Aesthetic: "clean DIY IoT prototype build log photo", high fidelity, no text watermark.
```

---

## 🔋 DEVICE-ACCURATE ANCHORS
Use these exact phrases depending on the node (pick the 3–6 that match):

- **Boards:** `ESP32-DevKitC V1 (WROOM-32, 2.4GHz antenna)`, `ESP8266 NodeMCU`, `ESP32-CAM with OV2640 + PIR`
- **Sensors:** `soil moisture capacitive probe`, `MQ-6 LPG gas sensor module`, `MQ-2 smoke sensor`, `DHT22 temperature-humidity`, `HC-SR04 ultrasonic module`, `PIR motion sensor (HC-SR501)`, `reed switch magnet pair`, `ACS712 20A current sensor`, `BME280`, `PMS5003 particulate sensor`
- **Actuators:** `2-channel 5V relay module`, `12V solenoid water valve brass`, `12V 110dB piezo siren`, `A4988 stepper driver + NEMA17`, `SG90 servo`, `940nm IR LED`, `16A contactor`
- **Power:** `ATX PSU 5V/12V rail breakout`, `USB power bank`, `18650 with TP4056`, `12V 7Ah battery + buck converter`, `5.5x2.1mm barrel jack`, `DIN rail terminal blocks`
- **Enclosure:** `IP65 ABS junction box`, `DIN rail housing`, `3D-printed PETG case`, `clear cable gland`

---

## 📌 NODE-SPECIFIC PROMPT BLOCKS (append the matching one)

### NODE-A1 — GARDEN CONTROLLER
```
... [GLOBAL STYLE] ... Outdoor-rated IP65 ABS box mounted on a balcony wall,
ESP32 with 3 capacitive soil moisture probes on red/black/green wires,
blue rain sensor plate, LDR, PIR, inside box a 2-channel relay module and a
12V 5A barrel jack input, one lead going to a brass 12V solenoid water valve,
label "NODE-A1 GARDEN".
```

### NODE-B1 — KITCHEN SAFETY (CRITICAL)
```
... [GLOBAL STYLE] ... Kitchen wall bracket 2m high, MQ-6 gas sensor module
plus MQ-2 smoke sensor, DHT22, dedicated 2-channel relay module, red 12V
solenoid gas valve clearly labeled, small 12V piezo siren, wires color-coded,
prominent safety label "CRITICAL — TEST GAS FUNCTION", enclosure vents.
```

### NODE-C1 — WATER TANK & PUMP
```
... [GLOBAL STYLE] ... Near an overhead water tank, ESP32 with 5 float
switches (3 top tank + 2 sump) on colored wires, HC-SR04 ultrasonic aimed
down, ACS712 in a clamp ring, relay driving a 16A contactor,
dustproof DIN-rail housing, label "NODE-C1 WATER".
```

### NODE-D1 — LIVING ROOM COMFORT
```
... [GLOBAL STYLE] ... Central ceiling spot, ESP32 with 2 PIR, LDR, DHT22,
2 reed switches, 220V LED light relay, IR LED pointing at an AC indoor unit,
A4988 stepper driver with small stepper motor for a curtain,
compact enclosure, label "NODE-D1 LIVING".
```

### NODE-F1 — NIGHT SECURITY CAMERA
```
... [GLOBAL STYLE] ... ESP32-CAM module in a small weatherproof dome,
OV2640 lens, ring of IR LEDs glowing faint red, PIR sensor beside it,
mounted 2.5m high on a gate/bracket, microSD card visible edge,
label "NODE-F1 SECURITY".
```

### NODE-G2 — AIR QUALITY
```
... [GLOBAL STYLE] ... Living-room wall unit 1.5m high, PMS5003 particulate
sensor with its clear inlet/outlet tube, BME280, small LCD or status LED,
ESP32, wall-powered, label "NODE-G2 AIR".
```

### NODE-S1 — ELECTRICAL MONITOR (PANEL)
```
... [GLOBAL STYLE] ... Open electrical distribution box, DIN rail, ESP32 with
ACS712 current sensors each clipped around an insulated feeder wire,
terminal blocks, clear mains-isolation trace on PCB, tidy wiring,
label "NODE-S1 POWER MONITOR — ISOLATION BARRIER".
```

### NODE-S3 — PANIC BUTTON (battery)
```
... [GLOBAL STYLE] ... Small wall plate 1m high, a large red push button in a
red ring, ESP8266 NodeMCU in a tiny box powered by an 18650 + TP4056,
mini 12V siren, prominent "PANIC" label, compact, visible from hall.
```

### NODE-S5 — FIRE DETECTION (battery)
```
... [GLOBAL STYLE] ... Ceiling-mounted smoke detector style, MQ-2 sensor,
ESP8266, small buzzer, AA/18650 battery holder, ventilation slots,
label "NODE-S5 FIRE", white plastic shell.
```

### NODE-H1 — AQUARIUM
```
... [GLOBAL STYLE] ... Inside an aquarium cabinet, ESP32 with waterproof
DS18B20 temperature probe, feeder servo (SG90) mounted to a hopper,
relay for the aquarium heater/light, small float switch, water-tight
cable glands, label "NODE-H1 AQUARIUM".
```

---

## 🛰️ SYSTEM-OVERVIEW RENDER PROMPT (one hero image for the whole project)

```
... [GLOBAL STYLE] ... Wide flat-lay top-down photograph of the complete
2-floor SmartHome kit: an ESP32 controller board, 5-6 representative sensor
modules (gas, smoke, PIR, soil moisture, ultrasonic, camera), relay module,
12V solenoid valve, siren, 18650 battery + TP4056, ATX PSU rail,
IP65 ABS boxes, screwdriver + multimeter, labeled 'SMARTHOME PROTOTYPE'.
Professional product-kit hero shot.
```

---

## 📐 WIRING-DIAGRAM PROMPT (clean schematic-style render)

```
Schematic-style technical wiring diagram, top-down, vector clean lines,
black background, labeled connectors: ESP32 pin header, relay IN1/IN2,
sensor VCC/GND/OUT, clearly separated 230V mains zone marked with a red
dashed "MAINS — ISOLATE" boundary and a low-voltage zone, fuse symbol,
snubber across relay contacts, monochrome-on-dark "engineering blueprint".
```

---

## ✅ CHECKLIST BEFORE GENERATING
- [ ] Pick ONE node per image (or the hero/system shot).
- [ ] Paste GLOBAL STYLE + DEVICE ANCHORS + the chosen NODE block.
- [ ] Match the exact peripherals you will buy (don't render things you won't use).
- [ ] For AI models limited on text: shorten the node block to 1–2 sentences but KEEP the anchors and "label" phrase.
- [ ] Save outputs into `E:\SmartHome_Prototype_Complete_Docs\AUDIT\generated\` and cross-check against your BOM (02).

*End of Master Photo Prompt.*