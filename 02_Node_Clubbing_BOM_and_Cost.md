# 02_Node_Clubbing_BOM_and_Cost.md
# SmartHome Prototype — Node Clubbing Strategy & Complete BOM

**Version:** 1.0 | **Date:** August 2026

---

## Table of Contents
1. [Node Clubbing Philosophy](#1-node-clubbing-philosophy)
2. [Physical Node Map — 2 Floor Flat](#2-physical-node-map--2-floor-flat)
3. [Node-by-Node BOM](#3-node-by-node-bom)
4. [Common Components (Shared Across Nodes)](#4-common-components-shared-across-nodes)
5. [Total System BOM](#5-total-system-bom)
6. [Node Placement Guidelines](#6-node-placement-guidelines)
7. [Cable & Power Distribution](#7-cable--power-distribution)

---

## 1. Node Clubbing Philosophy

**Rule:** One ESP32 per "logical zone" — not one per sensor. This reduces cost, power points, and WiFi congestion.

**Clubbing Criteria:**
- Sensors within 5 meters of each other → Same node
- Sensors sharing power source → Same node
- Safety-critical sensors get dedicated nodes (no mixing with non-critical)
- High-power actuators (motors, pumps) get dedicated power, may share ESP32
- Camera nodes are always dedicated (ESP32-CAM is resource-intensive)

**Why Club?**
| Metric | Separate Node per Sensor | Clubbed Nodes |
|--------|------------------------|---------------|
| ESP32 Count | 40+ | 15 |
| Cost | ₹12,000+ | ₹4,500 |
| WiFi Clients | 40+ | 15 |
| Power Points | 40+ | 15 |
| Maintenance | Nightmare | Manageable |

---

## 2. Physical Node Map — 2 Floor Flat

```
GROUND FLOOR (GF)
┌─────────────────────────────────────────────────────────────────┐
│  GARDEN / BALCONY                                               │
│  ┌─────────────┐  Soil moisture ×3, Rain sensor, LDR, PIR       │
│  │ NODE-A1     │  Actuators: Water valve, Awning motor, Light  │
│  │ Garden Ctrl │  ESP32 + Relay module + Motor driver          │
│  └─────────────┘  Power: 12V 5A PSU (shared with pump)        │
│                                                                 │
│  KITCHEN                                                        │
│  ┌─────────────┐  MQ-6 Gas, MQ-2 Smoke, DHT22, Leak sensor    │
│  │ NODE-B1     │  Actuators: Exhaust relay, Gas valve OFF,    │
│  │ Kitchen Safe│  Siren relay, Water inlet solenoid            │
│  └─────────────┘  Power: 5V 2A adapter + 12V for valve        │
│                                                                 │
│  ┌─────────────┐  PIR motion → Light relay                     │
│  │ NODE-B2     │  Power: Shared with NODE-B1 or separate 5V   │
│  │ Kitchen Light│                                               │
│  └─────────────┘                                                │
│                                                                 │
│  WATER / PUMP AREA                                              │
│  ┌─────────────┐  Float switches ×5 (OH tank 3 + Sump 2)      │
│  │ NODE-C1     │  Ultrasonic HC-SR04 backup, ACS712 current   │
│  │ Water Mgmt  │  Actuators: Pump contactor, Pressure pump   │
│  └─────────────┘  Power: 5V from ATX PSU + 12V relay board    │
│                                                                 │
│  LIVING ROOM                                                    │
│  ┌─────────────┐  PIR ×2, LDR, DHT22, Reed switches ×2        │
│  │ NODE-D1     │  Actuators: Light relay, IR LED (AC control)│
│  │ Living Ctrl │  Curtain stepper motor (A4988)               │
│  └─────────────┘  Power: 5V 3A + 12V for motors               │
│                                                                 │
│  SECURITY — FRONT                                               │
│  ┌─────────────┐  ESP32-CAM + PIR + IR LEDs                    │
│  │ NODE-F1     │  SD card local storage                         │
│  │ Night Cam   │  Power: 5V 2A dedicated                       │
│  └─────────────┘                                                │
│                                                                 │
│  ┌─────────────┐  ESP32-CAM + Button + Microphone (optional)   │
│  │ NODE-F2     │  Power: 5V 2A dedicated                       │
│  │ Doorbell    │                                                │
│  └─────────────┘                                                │
│                                                                 │
│  ┌─────────────┐  Reed switches ×4 (doors/windows), PIR ×2     │
│  │ NODE-F3     │  SW-420 Glass break, Siren relay              │
│  │ Intrusion   │  Power: 12V 2A (siren needs 12V)            │
│  └─────────────┘                                                │
│                                                                 │
│  PANIC BUTTON (Wall-mounted, every floor)                       │
│  ┌─────────────┐  Physical push button → MQTT → Node-RED       │
│  │ NODE-S3_GF  │  Power: 18650 battery backup                │
│  │ Panic GF    │                                                │
│  └─────────────┘                                                │
│                                                                 │
│  ELECTRICAL PANEL                                               │
│  ┌─────────────┐  PZEM-004T (voltage, current, power, energy) │
│  │ NODE-S1     │  Contactor relay for emergency cutoff        │
│  │ Elec Monitor│  Power: 5V from panel itself                  │
│  └─────────────┘                                                │
└─────────────────────────────────────────────────────────────────┘

FIRST FLOOR (1F)
┌─────────────────────────────────────────────────────────────────┐
│  BEDROOM MASTER                                                 │
│  ┌─────────────┐  PIR, LDR, DHT22, Reed switch, IR LED        │
│  │ NODE-D2     │  Actuators: Light relay, Curtain motor        │
│  │ Bedroom Ctrl│  Power: 5V 2A                                 │
│  └─────────────┘                                                │
│                                                                 │
│  BEDROOM SECOND                                                 │
│  ┌─────────────┐  PIR, LDR, DHT22, Reed switch                  │
│  │ NODE-D3     │  Actuators: Light relay                        │
│  │ Bed2 Ctrl   │  Power: 5V 2A                                 │
│  └─────────────┘                                                │
│                                                                 │
│  BATHROOM MASTER                                                │
│  ┌─────────────┐  DHT22, PIR, Leak sensor, DS18B20 (geyser)     │
│  │ NODE-E1     │  Actuators: Exhaust relay, Geyser relay       │
│  │ Bath Master │  Water inlet solenoid (if leak detected)      │
│  └─────────────┘  Power: 5V 2A + 12V for solenoid              │
│                                                                 │
│  BATHROOM COMMON                                                │
│  ┌─────────────┐  DHT22, PIR, Leak sensor                       │
│  │ NODE-E2     │  Actuators: Exhaust relay, Light relay        │
│  │ Bath Common │  Power: 5V 2A                                 │
│  └─────────────┘                                                │
│                                                                 │
│  AIR QUALITY (Central Location)                                 │
│  ┌─────────────┐  PMS5003, MH-Z19B, CCS811                      │
│  │ NODE-G2     │  Actuators: Exhaust/ventilation relay         │
│  │ Air Quality │  Power: 5V 3A (PMS5003 needs 500mA peak)    │
│  └─────────────┘                                                │
│                                                                 │
│  AQUARIUM                                                       │
│  ┌─────────────┐  DS18B20, Float switch, TDS sensor (optional) │
│  │ NODE-H1     │  Actuators: Heater relay, Light relay,       │
│  │ Aquarium    │  Filter relay, Servo feeder, Top-up pump     │
│  └─────────────┘  Power: 5V 3A + 12V for pump                  │
│                                                                 │
│  FALL DETECTION (Hallway / Stair landing)                       │
│  ┌─────────────┐  LD2410B mmWave radar                           │
│  │ NODE-S4_1F  │  Power: 5V 1A                                 │
│  │ Fall Detect │                                                │
│  └─────────────┘                                                │
│                                                                 │
│  PANIC BUTTON 1F                                                │
│  ┌─────────────┐  Physical push button                           │
│  │ NODE-S3_1F  │  Power: 18650 battery backup                  │
│  │ Panic 1F    │                                                │
│  └─────────────┘                                                │
│                                                                 │
│  FIRE DETECTION (1F Hallway)                                    │
│  ┌─────────────┐  MQ-2 / Optical smoke sensor                   │
│  │ NODE-S5_1F  │  Power: 5V 1A                                 │
│  │ Fire 1F     │                                                │
│  └─────────────┘                                                │
└─────────────────────────────────────────────────────────────────┘

HUB (Old PC/Laptop)
┌─────────────────────────────────────────────────────────────────┐
│  Ubuntu Server + Docker                                          │
│  Home Assistant + Mosquitto + Node-RED + Frigate + InfluxDB    │
│  Power: UPS-backed                                               │
└─────────────────────────────────────────────────────────────────┘

MOBILE GUARD ROBOT (Optional)
┌─────────────────────────────────────────────────────────────────┐
│  ESP32-CAM + Motor driver + Ultrasonic + Battery pack           │
│  NODE-F4 — Dedicated ESP32, not fixed location                  │
└─────────────────────────────────────────────────────────────────┘
```

---

## 3. Node-by-Node BOM

### NODE-A1: Garden / Balcony Controller
| Component | Model | Qty | Unit ₹ | Total ₹ | Source |
|-----------|-------|-----|--------|---------|--------|
| ESP32 DevKit | ESP32-WROOM-32 | 1 | 280 | 280 | Robu.in |
| Capacitive Soil Moisture | v1.2 | 3 | 90 | 270 | Amazon.in |
| Rain Drop Sensor | FC-37 | 1 | 60 | 60 | ElectronicsComp |
| LDR Module | GL5516 + LM393 | 1 | 40 | 40 | Local market |
| PIR Sensor | HC-SR501 | 1 | 70 | 70 | Robu.in |
| 12V Solenoid Valve | ½" brass, NC | 1 | 450 | 450 | Amazon.in |
| 12V Water Pump | 5W mini diaphragm | 1 | 350 | 350 | Amazon.in |
| L298N Motor Driver | Dual H-bridge | 1 | 120 | 120 | Robu.in |
| 12V DC Motor | 30 RPM, 10kg-cm | 1 | 250 | 250 | Amazon.in |
| 5V Relay Module | 4-channel | 1 | 120 | 120 | ElectronicsComp |
| 12V 5A PSU | SMPS | 1 | 350 | 350 | Local market |
| Project Box | IP65, 200×150×100 | 1 | 180 | 180 | Amazon.in |
| Jumper Wires | M-M, M-F, F-F set | 1 | 80 | 80 | Local market |
| Terminal Block | 10A, 12-position | 1 | 40 | 40 | Local market |
| **NODE-A1 Total** | | | | **₹2,660** | |

### NODE-B1: Kitchen Safety (CRITICAL)
| Component | Model | Qty | Unit ₹ | Total ₹ | Source |
|-----------|-------|-----|--------|---------|--------|
| ESP32 DevKit | ESP32-WROOM-32 | 1 | 280 | 280 | Robu.in |
| MQ-6 LPG Sensor | MQ-6 module | 1 | 150 | 150 | Amazon.in |
| MQ-2 Smoke Sensor | MQ-2 module | 1 | 120 | 120 | ElectronicsComp |
| DHT22 / BME280 | DHT22 (temp/hum) | 1 | 180 | 180 | Amazon.in |
| Water Leak Sensor | Rain sensor module | 1 | 50 | 50 | Local market |
| 5V Relay Module | 4-channel opto-isolated | 1 | 150 | 150 | Amazon.in |
| 12V Gas Solenoid Valve | Certified brass, NC, ½" | 1 | 1,200 | 1,200 | Amazon.in / Local gas shop |
| 12V Water Solenoid Valve | Brass, NC, ½" | 1 | 450 | 450 | Amazon.in |
| 12V Siren | Piezo electronic | 1 | 180 | 180 | Local market |
| 12V 3A PSU | SMPS | 1 | 250 | 250 | Local market |
| 5V 2A Adapter | USB type | 1 | 150 | 150 | Local market |
| Project Box | IP65, metal base | 1 | 250 | 250 | Amazon.in |
| Fuse Holder + Fuse | 2A glass fuse | 2 | 20 | 40 | Local market |
| **NODE-B1 Total** | | | | **₹3,450** | |

### NODE-B2: Kitchen Light (can merge with B1 if close)
| Component | Model | Qty | Unit ₹ | Total ₹ | Source |
|-----------|-------|-----|--------|---------|--------|
| ESP8266 NodeMCU | ESP8266MOD | 1 | 180 | 180 | Robu.in |
| PIR Sensor | HC-SR501 | 1 | 70 | 70 | Robu.in |
| 5V Relay Module | 1-channel | 1 | 50 | 50 | Local market |
| **NODE-B2 Total** | | | | **₹300** | |

### NODE-C1: Water Tank & Pump Management (CRITICAL)
| Component | Model | Qty | Unit ₹ | Total ₹ | Source |
|-----------|-------|-----|--------|---------|--------|
| ESP32 DevKit | ESP32-WROOM-32 | 1 | 280 | 280 | Robu.in |
| Float Switch | PP, vertical, NC/NO | 5 | 80 | 400 | Amazon.in |
| Ultrasonic Sensor | HC-SR04 | 1 | 80 | 80 | ElectronicsComp |
| ACS712 Current Sensor | 20A module | 1 | 120 | 120 | Robu.in |
| 5V Relay Module | 2-channel | 1 | 80 | 80 | ElectronicsComp |
| 25A Contactor | 230V AC coil | 1 | 350 | 350 | Local electrical shop |
| Pressure Switch | Off-the-shelf pump switch | 1 | 250 | 250 | Local pump shop |
| Project Box | IP65, large | 1 | 200 | 200 | Amazon.in |
| **NODE-C1 Total** | | | | **₹1,760** | |

### NODE-D1: Living Room Comfort
| Component | Model | Qty | Unit ₹ | Total ₹ | Source |
|-----------|-------|-----|--------|---------|--------|
| ESP32 DevKit | ESP32-WROOM-32 | 1 | 280 | 280 | Robu.in |
| PIR Sensor | HC-SR501 | 2 | 70 | 140 | Robu.in |
| LDR Module | GL5516 + LM393 | 1 | 40 | 40 | Local market |
| DHT22 | Temp/Humidity | 1 | 180 | 180 | Amazon.in |
| Reed Switch | Magnetic, NC | 2 | 25 | 50 | Local market |
| IR LED + Receiver | 940nm + TSOP1838 | 1 | 50 | 50 | ElectronicsComp |
| 5V Relay Module | 4-channel | 1 | 120 | 120 | ElectronicsComp |
| Stepper Motor | 28BYJ-48 | 1 | 120 | 120 | Robu.in |
| A4988 Driver | Stepper driver | 1 | 80 | 80 | Robu.in |
| 5V 3A Adapter | SMPS | 1 | 200 | 200 | Local market |
| Project Box | ABS, 150×100×70 | 1 | 120 | 120 | Amazon.in |
| **NODE-D1 Total** | | | | **₹1,400** | |

### NODE-D2: Master Bedroom Comfort
| Component | Model | Qty | Unit ₹ | Total ₹ | Source |
|-----------|-------|-----|--------|---------|--------|
| ESP32 DevKit | ESP32-WROOM-32 | 1 | 280 | 280 | Robu.in |
| PIR Sensor | HC-SR501 | 1 | 70 | 70 | Robu.in |
| LDR Module | GL5516 + LM393 | 1 | 40 | 40 | Local market |
| DHT22 | Temp/Humidity | 1 | 180 | 180 | Amazon.in |
| Reed Switch | Magnetic | 1 | 25 | 25 | Local market |
| IR LED + Receiver | 940nm + TSOP1838 | 1 | 50 | 50 | ElectronicsComp |
| 5V Relay Module | 2-channel | 1 | 80 | 80 | ElectronicsComp |
| 5V 2A Adapter | SMPS | 1 | 150 | 150 | Local market |
| Project Box | ABS, 120×80×50 | 1 | 80 | 80 | Amazon.in |
| **NODE-D2 Total** | | | | **₹955** | |

### NODE-D3: Second Bedroom (Minimal)
| Component | Model | Qty | Unit ₹ | Total ₹ | Source |
|-----------|-------|-----|--------|---------|--------|
| ESP8266 NodeMCU | ESP8266MOD | 1 | 180 | 180 | Robu.in |
| PIR Sensor | HC-SR501 | 1 | 70 | 70 | Robu.in |
| LDR Module | GL5516 + LM393 | 1 | 40 | 40 | Local market |
| DHT22 | Temp/Humidity | 1 | 180 | 180 | Amazon.in |
| Reed Switch | Magnetic | 1 | 25 | 25 | Local market |
| 5V Relay Module | 1-channel | 1 | 50 | 50 | Local market |
| 5V 2A Adapter | SMPS | 1 | 150 | 150 | Local market |
| Project Box | ABS, small | 1 | 60 | 60 | Amazon.in |
| **NODE-D3 Total** | | | | **₹755** | |

### NODE-E1: Master Bathroom
| Component | Model | Qty | Unit ₹ | Total ₹ | Source |
|-----------|-------|-----|--------|---------|--------|
| ESP32 DevKit | ESP32-WROOM-32 | 1 | 280 | 280 | Robu.in |
| DHT22 | Temp/Humidity | 1 | 180 | 180 | Amazon.in |
| PIR Sensor | HC-SR501 | 1 | 70 | 70 | Robu.in |
| Water Leak Sensor | Rain sensor module | 1 | 50 | 50 | Local market |
| DS18B20 Waterproof | 1m probe | 1 | 120 | 120 | Amazon.in |
| 5V Relay Module | 3-channel | 1 | 100 | 100 | ElectronicsComp |
| 12V Solenoid Valve | Brass, NC, ½" | 1 | 450 | 450 | Amazon.in |
| 5V 2A Adapter | SMPS | 1 | 150 | 150 | Local market |
| Project Box | IP65 | 1 | 150 | 150 | Amazon.in |
| **NODE-E1 Total** | | | | **₹1,550** | |

### NODE-E2: Common Bathroom
| Component | Model | Qty | Unit ₹ | Total ₹ | Source |
|-----------|-------|-----|--------|---------|--------|
| ESP8266 NodeMCU | ESP8266MOD | 1 | 180 | 180 | Robu.in |
| DHT22 | Temp/Humidity | 1 | 180 | 180 | Amazon.in |
| PIR Sensor | HC-SR501 | 1 | 70 | 70 | Robu.in |
| Water Leak Sensor | Rain sensor module | 1 | 50 | 50 | Local market |
| 5V Relay Module | 2-channel | 1 | 80 | 80 | ElectronicsComp |
| 5V 2A Adapter | SMPS | 1 | 150 | 150 | Local market |
| Project Box | ABS | 1 | 80 | 80 | Amazon.in |
| **NODE-E2 Total** | | | | **₹790** | |

### NODE-F1: Night Security Camera
| Component | Model | Qty | Unit ₹ | Total ₹ | Source |
|-----------|-------|-----|--------|---------|--------|
| ESP32-CAM | AI-Thinker module + programmer | 1 | 450 | 450 | Robu.in |
| PIR Sensor | Mini PIR (AM312) | 1 | 60 | 60 | Amazon.in |
| IR LED Array | 48 LEDs, 940nm, 5V | 1 | 180 | 180 | Amazon.in |
| Micro SD Card | 32GB Class 10 | 1 | 350 | 350 | Amazon.in |
| 5V 2A Adapter | Dedicated | 1 | 150 | 150 | Local market |
| Project Box | IP65, with glass front | 1 | 200 | 200 | Amazon.in |
| **NODE-F1 Total** | | | | **₹1,390** | |

### NODE-F2: Video Doorbell
| Component | Model | Qty | Unit ₹ | Total ₹ | Source |
|-----------|-------|-----|--------|---------|--------|
| ESP32-CAM | AI-Thinker + programmer | 1 | 450 | 450 | Robu.in |
| Push Button | Weatherproof, NO | 1 | 40 | 40 | Local market |
| Micro SD Card | 16GB | 1 | 250 | 250 | Amazon.in |
| 5V 2A Adapter | SMPS | 1 | 150 | 150 | Local market |
| Project Box | IP65, door-mount | 1 | 180 | 180 | Amazon.in |
| **NODE-F2 Total** | | | | **₹1,070** | |

### NODE-F3: Intrusion Alarm System
| Component | Model | Qty | Unit ₹ | Total ₹ | Source |
|-----------|-------|-----|--------|---------|--------|
| ESP32 DevKit | ESP32-WROOM-32 | 1 | 280 | 280 | Robu.in |
| Reed Switch | Magnetic, NC | 4 | 25 | 100 | Local market |
| PIR Sensor | HC-SR501 | 2 | 70 | 140 | Robu.in |
| Vibration Sensor | SW-420 (glass break) | 1 | 50 | 50 | ElectronicsComp |
| 12V Siren | Piezo electronic | 1 | 180 | 180 | Local market |
| 5V Relay Module | 1-channel | 1 | 50 | 50 | Local market |
| 12V 2A PSU | SMPS | 1 | 250 | 250 | Local market |
| Project Box | Metal, with tamper switch | 1 | 300 | 300 | Amazon.in |
| **NODE-F3 Total** | | | | **₹1,350** | |

### NODE-F4: Mobile Guard Robot (Optional)
| Component | Model | Qty | Unit ₹ | Total ₹ | Source |
|-----------|-------|-----|--------|---------|--------|
| ESP32-CAM | AI-Thinker | 1 | 450 | 450 | Robu.in |
| L298N Motor Driver | Dual H-bridge | 1 | 120 | 120 | Robu.in |
| DC Motor + Wheel | 3–6V, 65mm wheel | 2 | 80 | 160 | Amazon.in |
| Ultrasonic Sensor | HC-SR04 | 1 | 80 | 80 | ElectronicsComp |
| Chassis | Acrylic 2WD kit | 1 | 250 | 250 | Amazon.in |
| 18650 Battery | 3.7V, 2000mAh | 2 | 150 | 300 | Amazon.in |
| Battery Holder | 2×18650 with BMS | 1 | 120 | 120 | Amazon.in |
| TP4056 Charger | USB Li-ion | 1 | 40 | 40 | ElectronicsComp |
| MT3608 Boost | 5V output | 1 | 30 | 30 | ElectronicsComp |
| **NODE-F4 Total** | | | | **₹1,550** | |

### NODE-G2: Air Quality Monitor
| Component | Model | Qty | Unit ₹ | Total ₹ | Source |
|-----------|-------|-----|--------|---------|--------|
| ESP32 DevKit | ESP32-WROOM-32 | 1 | 280 | 280 | Robu.in |
| PMS5003 | PM2.5/PM10 sensor | 1 | 1,200 | 1,200 | Amazon.in |
| MH-Z19B | CO2 sensor | 1 | 1,800 | 1,800 | Amazon.in |
| CCS811 | VOC/eCO2 sensor | 1 | 350 | 350 | Amazon.in |
| 5V Relay Module | 1-channel | 1 | 50 | 50 | Local market |
| 5V 3A Adapter | SMPS | 1 | 200 | 200 | Local market |
| Project Box | Vented ABS | 1 | 150 | 150 | Amazon.in |
| **NODE-G2 Total** | | | | **₹4,030** | |

### NODE-H1: Aquarium Automation
| Component | Model | Qty | Unit ₹ | Total ₹ | Source |
|-----------|-------|-----|--------|---------|--------|
| ESP32 DevKit | ESP32-WROOM-32 | 1 | 280 | 280 | Robu.in |
| DS18B20 Waterproof | 1m probe | 1 | 120 | 120 | Amazon.in |
| Float Switch | Mini, vertical | 1 | 60 | 60 | Amazon.in |
| TDS Sensor | Analog, water quality | 1 | 200 | 200 | Amazon.in |
| SG90 Servo | 9g micro servo | 1 | 80 | 80 | Robu.in |
| 5V Relay Module | 4-channel | 1 | 120 | 120 | ElectronicsComp |
| 5V Mini Pump | USB submersible | 1 | 200 | 200 | Amazon.in |
| 5V 3A Adapter | SMPS | 1 | 200 | 200 | Local market |
| Project Box | ABS | 1 | 100 | 100 | Amazon.in |
| **NODE-H1 Total** | | | | **₹1,360** | |

### NODE-S1: Electrical Monitoring (CRITICAL)
| Component | Model | Qty | Unit ₹ | Total ₹ | Source |
|-----------|-------|-----|--------|---------|--------|
| ESP32 DevKit | ESP32-WROOM-32 | 1 | 280 | 280 | Robu.in |
| PZEM-004T v3.0 | AC energy monitor | 1 | 650 | 650 | Amazon.in |
| Current Transformer | 100A clamp (included) | 1 | 0 | 0 | With PZEM |
| 25A Contactor | Emergency cutoff | 1 | 350 | 350 | Local electrical shop |
| 5V Relay Module | 1-channel | 1 | 50 | 50 | Local market |
| 5V 1A Adapter | From panel tap | 1 | 0 | 0 | Reuse phone charger |
| Project Box | Metal, DIN rail mount | 1 | 250 | 250 | Amazon.in |
| **NODE-S1 Total** | | | | **₹1,580** | |

### NODE-S3: Panic Buttons (×2, one per floor)
| Component | Model | Qty | Unit ₹ | Total ₹ | Source |
|-----------|-------|-----|--------|---------|--------|
| ESP8266 NodeMCU | ESP8266MOD | 1 | 180 | 180 | Robu.in |
| Push Button | Latching, red, large | 1 | 50 | 50 | Local market |
| 18650 Battery | 3.7V, 2000mAh | 1 | 150 | 150 | Amazon.in |
| Battery Holder | Single 18650 | 1 | 30 | 30 | ElectronicsComp |
| TP4056 Charger | USB Li-ion | 1 | 40 | 40 | ElectronicsComp |
| Project Box | Wall-mount, red label | 1 | 80 | 80 | Amazon.in |
| **Per Panic Node** | | | | **₹530** | |
| **×2 Total** | | | | **₹1,060** | |

### NODE-S4: Fall Detection (1F Hallway)
| Component | Model | Qty | Unit ₹ | Total ₹ | Source |
|-----------|-------|-----|--------|---------|--------|
| ESP32 DevKit | ESP32-WROOM-32 | 1 | 280 | 280 | Robu.in |
| LD2410B | mmWave radar sensor | 1 | 450 | 450 | Amazon.in |
| 5V 1A Adapter | SMPS | 1 | 100 | 100 | Local market |
| Project Box | ABS, ceiling mount | 1 | 80 | 80 | Amazon.in |
| **NODE-S4 Total** | | | | **₹910** | |

### NODE-S5: Fire Detection (×2, GF + 1F)
| Component | Model | Qty | Unit ₹ | Total ₹ | Source |
|-----------|-------|-----|--------|---------|--------|
| ESP8266 NodeMCU | ESP8266MOD | 1 | 180 | 180 | Robu.in |
| MQ-2 / Optical Smoke | OPT101 based | 1 | 200 | 200 | Amazon.in |
| 5V Buzzer | Active piezo | 1 | 30 | 30 | Local market |
| 5V 1A Adapter | SMPS | 1 | 100 | 100 | Local market |
| Project Box | ABS, ceiling mount | 1 | 80 | 80 | Amazon.in |
| **Per Fire Node** | | | | **₹590** | |
| **×2 Total** | | | | **₹1,180** | |

---

## 4. Common Components (Shared Across Nodes)

| Component | Qty | Unit ₹ | Total ₹ | Source |
|-----------|-----|--------|---------|--------|
| Breadboards (830 tie-point) | 5 | 60 | 300 | Local market |
| Jumper Wire Kit (120pcs) | 3 | 100 | 300 | Local market |
| Dupont Connector Kit | 1 | 250 | 250 | Amazon.in |
| Resistor Kit (400pcs) | 1 | 120 | 120 | Amazon.in |
| Capacitor Kit | 1 | 150 | 150 | Amazon.in |
| PCB Prototype Boards (5×7cm) | 10 | 15 | 150 | Local market |
| Heat Shrink Tube Set | 1 | 100 | 100 | Local market |
| Cable Ties (100pcs) | 1 | 50 | 50 | Local market |
| Label Printer Tape / Stickers | 1 | 100 | 100 | Amazon.in |
| Multimeter (basic) | 1 | 300 | 300 | Local market |
| Soldering Iron Kit | 1 | 400 | 400 | Amazon.in |
| Solder Wire (50g) | 1 | 80 | 80 | Local market |
| Flux Pen | 1 | 40 | 40 | Local market |
| Desoldering Pump | 1 | 60 | 60 | Local market |
| Wire Stripper | 1 | 80 | 80 | Local market |
| DIN Rail (1 meter) | 2 | 120 | 240 | Local electrical shop |
| Terminal Blocks (assorted) | 1 set | 200 | 200 | Local market |
| Fuse Holders + Fuses (assorted) | 1 set | 150 | 150 | Local market |
| **Common Total** | | | **₹3,120** | |

---

## 5. Total System BOM

| Category | Nodes | Cost (₹) |
|----------|-------|----------|
| Garden / Balcony (A1) | 1 | 2,660 |
| Kitchen Safety (B1) | 1 | 3,450 |
| Kitchen Light (B2) | 1 | 300 |
| Water / Pump (C1) | 1 | 1,760 |
| Living Room (D1) | 1 | 1,400 |
| Master Bedroom (D2) | 1 | 955 |
| Second Bedroom (D3) | 1 | 755 |
| Master Bathroom (E1) | 1 | 1,550 |
| Common Bathroom (E2) | 1 | 790 |
| Night Camera (F1) | 1 | 1,390 |
| Video Doorbell (F2) | 1 | 1,070 |
| Intrusion Alarm (F3) | 1 | 1,350 |
| Guard Robot (F4) | 1 | 1,550 |
| Air Quality (G2) | 1 | 4,030 |
| Aquarium (H1) | 1 | 1,360 |
| Electrical Monitor (S1) | 1 | 1,580 |
| Panic Buttons (S3) | 2 | 1,060 |
| Fall Detection (S4) | 1 | 910 |
| Fire Detection (S5) | 2 | 1,180 |
| Common Components | — | 3,120 |
| **GRAND TOTAL** | **20 nodes** | **₹32,320** |

**Buffer (10% for replacements/mistakes):** ₹3,232  
**Additional Safety Component Upgrade Margin:** ₹2,000  
**Final Estimated Budget:** **₹37,500**

*\*Note: The final estimated budget has been increased to ₹37,500 to incorporate a dedicated ₹2,000 safety buffer. This ensures that safety-critical nodes use premium, certified solenoids, heavy-duty contactors, and high-quality fuses instead of low-cost generic hardware. See 13_Cost_Estimate_Summary.md for details.*

---

## 6. Node Placement Guidelines

| Node | Recommended Location | Mounting | Notes |
|------|---------------------|----------|-------|
| A1 | Balcony wall, under shade | Screws + IP65 box | Away from direct rain |
| B1 | Kitchen wall, 2m height | Screws | MQ-6 30cm below ceiling |
| B2 | Kitchen ceiling corner | Magnetic / Command strips | Near entry |
| C1 | Near pump/motor | DIN rail in utility area | Away from water splash |
| D1 | Living room ceiling | Recessed or surface | Central location |
| D2/D3 | Bedroom ceiling / wall | Command strips | Near AC for IR |
| E1/E2 | Bathroom ceiling, outside wet area | IP65 box, high mount | Exhaust fan wiring nearby |
| F1 | Front balcony / gate | Security screws, height 2.5m | Tamper-proof |
| F2 | Door frame, 1.5m height | Screws | Weatherproof |
| F3 | Central hallway ceiling | Recessed | Siren audible everywhere |
| G2 | Living room wall, 1.5m | Command strips | Away from windows |
| H1 | Aquarium cabinet | Inside cabinet, ventilated | Away from water splash |
| S1 | Inside electrical panel | DIN rail | Licensed electrician review |
| S3 | Wall, 1m height, both floors | Screws | Red label, easy reach |
| S4 | 1F hallway ceiling | Recessed | 2.5m height, wide coverage |
| S5 | Hallway ceiling, both floors | Recessed | Central location |

---

## 7. Cable & Power Distribution

### Power Plan
```
ATX PSU (from old PC) ──► 5V rail ──► USB hub ──► Multiple 5V nodes
                    ──► 12V rail ──► Terminal block ──► 12V devices

Individual Adapters:
  - B1: 12V 3A (gas valve + siren)
  - C1: 12V 2A (contactor coil)
  - F3: 12V 2A (siren)
  - A1: 12V 5A (pump + motor + valve)
```

⚠️ **ATX PSU Minimum Load Resistor Note:** Most PC ATX power supplies require a minimum load on the 5V and/or 3.3V rail (typically a 10 ohm, 10W or 25W metal power resistor connected between a red wire (+5V) and a black wire (GND)) to regulate the output voltage properly. Without this load, the 12V rail may float, drop below 10V, or shut down entirely under load. See 01_System_Architecture_and_Hub_Setup.md Section 13 for wiring details.

### Cable Types Needed
| Type | Gauge | Usage | Est. Length |
|------|-------|-------|-------------|
| Cat 5e/6 Ethernet | — | Cameras, hub to router | 20m |
| 2-core flexible | 0.75mm² | Low voltage sensors, 5V | 50m |
| 2-core flexible | 1.5mm² | 12V actuators, solenoids | 30m |
| 3-core flexible | 2.5mm² | 230V AC (contactors, pumps) | 20m |
| Dupont jumper wires | — | Breadboard/prototype | 3 sets |
| Heat shrink | assorted | Waterproofing joints | 1 set |

---

*End of 02_Node_Clubbing_BOM_and_Cost.md*
*Next: 03_Scrap_Reuse_Guide.md*
