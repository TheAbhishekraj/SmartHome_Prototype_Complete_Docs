# 00_Project_Master_Plan.md
# SmartHome Prototype — Whole-Home Automation for 2-Floor Flat
## Project Master Plan & CTO Blueprint

**Version:** 1.0  
**Date:** August 2026  
**Author:** Senior Home Automation Engineer / IoT Solutions Architect  
**Target:** 2-Floor Flat (~2000 sq ft) → Boutique Commercial Product  
**Budget Philosophy:** Minimal cost, maximum safety, modular scalability  
**Core Stack:** ESP32/ESP8266 + Home Assistant + Mosquitto MQTT + Node-RED + Old PC Hub  

---

## Table of Contents

1. [Executive Summary](#1-executive-summary)
2. [Project Vision & Commercialization Goals](#2-project-vision--commercialization-goals)
3. [Design Philosophy & Constraints](#3-design-philosophy--constraints)
4. [Scope Overview — Zones & Automations](#4-scope-overview--zones--automations)
5. [Expert Additions (CTO Recommendations)](#5-expert-additions-cto-recommendations)
6. [System Architecture at a Glance](#6-system-architecture-at-a-glance)
7. [Documentation Suite Index](#7-documentation-suite-index)
8. [Build Phases & Timeline](#8-build-phases--timeline)
9. [Risk Assessment & Mitigation](#9-risk-assessment--mitigation)
10. [Budget Overview](#10-budget-overview)
11. [Success Criteria & KPIs](#11-success-criteria--kpis)
12. [Next Steps](#12-next-steps)

---

## 1. Executive Summary

This project designs, builds, and documents a **complete whole-home automation system** for a 2-floor, ~2000 sq ft residential flat using ESP32/ESP8266 microcontrollers as distributed nodes, an **old PC/laptop as the central hub** running Home Assistant, and a mix of **salvaged scrap components** and **new certified safety-critical parts**.

The system covers **8 primary zones** with **40+ automations**, including garden watering, kitchen gas safety, water tank management, climate control, security cameras, cleaning robots, aquarium automation, and whole-house electrical safety monitoring.

**Key Differentiators:**
- **Zero cloud dependency** — fully local control with optional Tailscale/Cloudflare remote access
- **Scrap-first procurement** — old smartphones, PCs, ATX supplies, routers, speakers, and webcams repurposed
- **Safety-certified new parts only for mains/gas/water** — no compromises on life-safety systems
- **Simulation-first development** — every node prototyped in Wokwi before physical build
- **Commercialization-ready documentation** — designed to evolve from prototype → custom PCB → branded kit → scaled product
- **Tenant-friendly design** — non-destructive installation, reversible modifications, clear labeling

**Estimated prototype cost:** ₹35,000–₹50,000 (US$420–$600) for complete 2-floor system  
**Estimated commercial kit cost (at scale):** ₹18,000–₹25,000 per home  
**Target selling price:** ₹45,000–₹65,000 per installation (60%+ margin)

---

## 2. Project Vision & Commercialization Goals

### 2.1 Prototype Phase (Months 1–3)
**Goal:** Build a fully functional, reliable automation system for your own 2-floor flat that you use daily. Document everything. Prove reliability over 30+ days of continuous operation.

**Deliverables:**
- 12–15 physical ESP32/ESP8266 nodes deployed across 2 floors
- Home Assistant dashboard with 50+ entities
- Node-RED automations for all safety-critical systems
- Complete BOM with Indian procurement links
- All firmware in version-controlled ESPHome YAML
- Wokwi simulations for every node type

### 2.2 Refinement Phase (Months 4–6)
**Goal:** Harden the system based on real-world usage. Optimize for power failures, WiFi drops, sensor drift, and false alarms. Reduce cost per node by 20%.

**Deliverables:**
- OTA firmware update pipeline established
- Custom PCB designs in EasyEDA for 3 most common node types
- Power backup (UPS) strategy for all critical nodes
- Mesh WiFi coverage verified across both floors
- User feedback loop established (family/tenant usability testing)

### 2.3 Custom PCB Phase (Months 7–9)
**Goal:** Replace breadboard/prototype wiring with professional 2-layer PCBs. Design for manufacturability (DFM).

**Deliverables:**
- 3–5 custom PCB designs (sensor node, relay node, safety node, camera node)
- JLCPCB prototype batch (10 sets) at ₹150–₹300 per PCB
- Enclosure design (3D printed or off-the-shelf IP-rated boxes)
- CE/FCC pre-compliance documentation started
- Firmware standardized per PCB variant

### 2.4 Branded Kit Phase (Months 10–14)
**Goal:** Package as a sellable "Smart Flat Starter Kit" for Indian market. Include installation manual, pre-flashed nodes, and 1-year support.

**Deliverables:**
- Branded packaging and documentation
- Pre-configured Home Assistant image (ready to flash to old PC)
- Installation video series (Hindi + English)
- Pilot installations in 3–5 homes (friends/family at cost price)
- Word-of-mouth marketing via real installation showcases

### 2.5 Scaling Phase (Months 15–24)
**Goal:** Transition from bespoke installations to a repeatable product. Explore B2B partnerships with builders/renovators.

**Deliverables:**
- Standardized 3-tier product lines (Basic / Standard / Premium)
- Local assembly partnership or small manufacturing unit
- Android/iOS companion app (optional, web-based PWA preferred)
- Channel partner network in 2–3 cities
- Target: 50 installations in Year 1, 200 in Year 2

---

## 3. Design Philosophy & Constraints

### 3.1 Core Principles

| Principle | Implementation |
|-----------|----------------|
| **Safety First** | New certified components for all mains (230V AC), gas, and water valve interfaces. Fuses on every line. Isolation transformers where needed. |
| **Local-First** | No mandatory cloud services. Home Assistant runs entirely on local old PC. MQTT broker local. Internet only for mobile notifications (optional). |
| **Scrap Reuse** | Old smartphones → wall tablets/dashboards. Old PC → Home Assistant hub. ATX PSU → 5V/12V DC power rail. Old routers → WiFi APs or MQTT nodes. |
| **Modularity** | Each node does one thing well. Nodes communicate via MQTT. Failed node = swap in 5 minutes, not system down. |
| **Simulation Before Soldering** | Every node prototyped in Wokwi. Logic verified. Thresholds tuned. Only then built physically. |
| **Tenant-Friendly** | No wall cutting. Command strips, magnetic mounts, existing switch boxes. Reversible installation. Clear labeling. |
| **Document Everything** | Every node gets a README. Every YAML file is commented. Every wire is labeled. Git tracks all changes. |

### 3.2 Technical Constraints

| Constraint | Rationale |
|------------|-----------|
| **ESP32 / ESP8266 only** | Cost-effective, WiFi-native, excellent ESPHome support, huge community |
| **Old PC / Laptop hub** | Zero additional cost, more powerful than Raspberry Pi, easy to repair, SATA storage for video |
| **No Raspberry Pi** | User preference; avoids Pi shortage/pricing issues; leverages existing e-waste |
| **ESPHome YAML primary** | Declarative, OTA-capable, Home Assistant native integration, beginner-friendly |
| **Arduino C++ secondary** | Only when ESPHome lacks support (e.g., complex motor control, custom protocols) |
| **Indian procurement** | Robu.in, ElectronicsComp, Amazon.in, Thingbits, Sunrom, Flyrobo, local Lajpat Rai / SP Road equivalents |

### 3.3 Non-Negotiable Safety Rules

1. **All 230V AC switching uses certified relays/contactors** with snubber circuits and fuse protection
2. **Gas solenoid valves are certified for LPG/Natural Gas** — no homemade solutions
3. **Water valves are food-grade brass/stainless** — no plastic on mains pressure
4. **Every mains node has a clear emergency cutoff switch** within arm's reach
5. **Ground (Earth) connection verified** on all metal enclosures and AC lines
6. **No live circuit work** — always power down, verify with multimeter, then work
7. **GFCI/ELCB protection** on all automation circuits sharing space with water
8. **Fire-rated enclosures** (ABS V-0 or metal) for any node near heat sources

---

## 4. Scope Overview — Zones & Automations

### Zone A: Garden / Balcony
| Automation | Sensors | Actuators | Safety Notes |
|------------|---------|-----------|--------------|
| A1. Smart Plant Watering | Capacitive soil moisture (v1.2) | 12V solenoid valve, small pump | Waterproof connections, timer-based backup cutoff |
| A2. Rain Protection Awning | Rain drop sensor, wind sensor (optional) | 12V/24V DC motor + L298N driver | Motor limit switches mandatory |
| A3. Outdoor Lighting | LDR (GL5516), PIR (HC-SR501) | 5V relay module → LED driver | Weatherproof enclosure IP65 |

### Zone B: Kitchen Safety
| Automation | Sensors | Actuators | Safety Notes |
|------------|---------|-----------|--------------|
| B1. Gas Leak Detection | MQ-6 LPG sensor | Exhaust fan relay, gas solenoid OFF, siren, mobile alert | MQ-6 needs 24hr burn-in, placed 30cm from ceiling |
| B2. Smoke/Fire Detection | MQ-2 or optical smoke (OPT101/TF0607) | Siren, mobile alert | Dual-sensor preferred (optical + ionization) |
| B3. Heat/Humidity Monitor | DHT22 or BME280 | Exhaust fan relay | BME280 more accurate, I2C bus |
| B4. Sink Leak Detection | Water leak sensor (rain sensor module) | Water inlet solenoid OFF | Place under sink basin, check weekly |
| B5. Kitchen Light Auto | PIR (HC-SR501) | Relay → existing light | Override wall switch retained |

### Zone C: Water & Motor Pump
| Automation | Sensors | Actuators | Safety Notes |
|------------|---------|-----------|--------------|
| C1. Overhead Tank Level | Float switches (3 levels) OR Ultrasonic (HC-SR04) | Pump contactor ON/OFF | Dry-run protection mandatory |
| C2. Sump Tank Level | Float switches (2 levels) | Alert only (or backup pump) | Prevent dry-run of sump pump |
| C3. Auto Pump Control | Float switches + Current sensor (ACS712) | Pump contactor | Dry-run = current < threshold → auto OFF |
| C4. Pressure Pump Control | Pressure switch (off-the-shelf) OR flow sensor | Pressure pump relay | Use certified pressure switch for safety |

### Zone D: Living / Bedroom Comfort
| Automation | Sensors | Actuators | Safety Notes |
|------------|---------|-----------|--------------|
| D1. Auto Lights | PIR + LDR | Relay → existing light | Dimming optional (PWM LED driver) |
| D2. Climate Control | DHT22 + IR LED (TSOP1838 receiver for learning) | IR blaster → AC/Fan | Learn existing remote codes first |
| D3. Auto Door Closure | Reed switch (door position) + Ultrasonic (obstacle) | Servo / motorized closer | Obstacle detection = anti-pinch |
| D4. Open Window/Door Alert | Reed switches on all openings | Mobile alert | Night mode + Away mode logic |
| D5. Curtain Automation | LDR or schedule | Stepper motor + driver (A4988) | Limit switches or current sensing for end stops |

### Zone E: Bathroom / Utility
| Automation | Sensors | Actuators | Safety Notes |
|------------|---------|-----------|--------------|
| E1. Exhaust Fan Control | DHT22 (humidity) + PIR | Relay → exhaust fan | Humidity threshold > 70% |
| E2. Geyser Control | DS18B20 (water temp probe) + Blynk/schedule | Relay → geyser | Thermal cutoff + timer redundancy |
| E3. Bathroom Leak | Water leak sensor | Water inlet solenoid OFF | Same as kitchen leak system |
| E4. Bathroom Light Auto | PIR | Relay → existing light | Delay 5 min after no motion |

### Zone F: Security & Camera
| Automation | Sensors | Actuators | Safety Notes |
|------------|---------|-----------|--------------|
| F1. Night Camera | ESP32-CAM + PIR + IR LED array | SD card local storage | 5V 2A power supply minimum |
| F2. Mobile Guard Robot | ESP32-CAM + Ultrasonic (HC-SR04) + Motor driver | 2x DC motors | Battery management critical |
| F3. Intrusion Alarm | Reed switches + PIR + Glass break sensor (SW-420 vibration) | Siren (12V piezo) | Entry/exit delay 30 seconds |
| F4. Video Doorbell | ESP32-CAM + Push button | Mobile notification + relay → door strike | Weatherproof, tamper-proof |

### Zone G: Cleaning & Inspection
| Automation | Sensors | Actuators | Safety Notes |
|------------|---------|-----------|--------------|
| G1. Robot Vacuum/Mop | Ready-made (Mi/Roborock) | Home Assistant integration | Scheduled daily runs |
| G2. Air Quality Monitor | PMS5003 (PM2.5) + MH-Z19B (CO2) + CCS811 (VOC) | Exhaust/ventilation relay | Place in living room, central location |
| G3. UV Sterilizer (Optional) | Timer-based | Relay → UV tube | Interlock: UV ON only when room empty (PIR) |
| G4. Drain Camera (Optional) | USB endoscope + old smartphone | Manual inspection only | Waterproof probe |

### Zone H: Aquarium Automation
| Automation | Sensors | Actuators | Safety Notes |
|------------|---------|-----------|--------------|
| H1. Temperature Control | DS18B20 waterproof | Relay → heater | Heater must have physical thermostat backup |
| H2. Light Schedule | Timer (ESPHome) | Relay → aquarium LED | Simulate dawn/dusk with PWM |
| H3. Auto Fish Feeder | SG90 servo or 28BYJ-48 stepper | Dispense mechanism | Feed once/twice daily, adjustable quantity |
| H4. Filter Pump Control | Schedule + manual override | Relay → filter pump | Never turn off for >2 hours |
| H5. Water Top-Up | Float switch (low level) | Small pump from reservoir | Overflow protection mandatory |

### Additional Whole-House Safety
| Automation | Sensors | Actuators | Safety Notes |
|------------|---------|-----------|--------------|
| S1. Electrical Monitoring | PZEM-004T (voltage, current, power, energy) | Contactor → mains cutoff | Non-invasive CT clamp for safety |
| S2. Whole-House Water Leak | Multiple leak sensors → Node-RED aggregation | Main inlet solenoid OFF | Manual override valve retained |
| S3. Panic Button | Physical push button (every floor) | Siren + mobile alert | Latching alarm, reset via dashboard |
| S4. Fall Detection | mmWave radar (LD2410B or Aqara FP2 via ESPHome proxy) | Mobile alert | Privacy-preserving, no camera |
| S5. Fire Detection (Per Room) | Smoke sensor in every room | Siren + mobile alert | Interconnected: one triggers all |
| S6. Air Quality / CO2 | MH-Z19B or SCD40 per room | Ventilation boost | SCD40 more accurate, I2C |
| S7. Sump/Overhead Overflow | Float switch at overflow level | Emergency pump + alert | Last line of defense |

---

## 5. Expert Additions (CTO Recommendations)

Beyond your excellent scope, I recommend adding the following high-value, low-cost automations:

### 5.1 Energy Monitoring & Smart Metering
- **Whole-house energy dashboard** using PZEM-004T per phase (single-phase or 3-phase)
- **Per-appliance monitoring** with Sonoff POW R2 or custom ESP32 + ACS712 on washing machine, fridge, AC
- **Solar integration ready** — design DC bus and monitoring points if solar is added later
- **Peak load alerts** — notify when approaching breaker limit (e.g., >15A on 16A circuit)

### 5.2 Voice Control Integration
- **Local voice processing** via Wyoming Protocol + Piper TTS + Whisper STT on the old PC
- **No Alexa/Google dependency** — fully private, works without internet
- **Satellite microphones** using old smartphones or cheap USB mics in each room
- **Wake word:** "Hey Jarvis" or "Hey Home" (customizable)

### 5.3 Predictive Maintenance Alerts
- **Washing machine vibration analysis** using SW-420 → predict bearing failure
- **Pump current signature analysis** → detect cavitation or impeller wear (ACS712)
- **Filter pressure differential** → alert when aquarium/clogged
- **Geyser heating time tracking** → alert when efficiency drops (sediment buildup)

### 5.4 Scene Modes
| Scene | Actions |
|-------|---------|
| **Morning** | Gradual lights, curtain open, geyser pre-heat, coffee maker ON (if added) |
| **Night** | All lights OFF, doors locked, cameras armed, garden watered, AC sleep mode |
| **Away** | All lights OFF, intrusion armed, leak monitoring active, simulated presence (random lights) |
| **Party** | Color lights (if RGB added), music sync, doorbell muted, AC boosted |
| **Movie** | Dim lights, curtain close, AC comfort, notification silence |
| **Emergency** | All lights ON, siren OFF (if false alarm), unlock doors, stop all motors |

### 5.5 Smart Door Lock Integration
- **Electronic door strike** or **smart deadbolt** with RFID/NFC (old smartphone as reader?)
- **PIN entry** with tamper alert (3 wrong attempts = alarm)
- **Temporary access codes** for guests/maids via Node-RED
- **Auto-lock** 30 seconds after door close (reed switch)

### 5.6 Water Quality Monitoring
- **TDS sensor** (Total Dissolved Solids) for drinking water → alert when RO filter needs change
- **pH sensor** for aquarium → critical for fish health
- **Flow rate monitoring** → detect pipe leaks (unexpected flow when all taps closed)

### 5.7 Enhanced Security
- **Facial recognition** on ESP32-CAM using ESP-WHO framework (limited but functional)
- **License plate recognition** for parking area (if applicable) using old webcam + OpenALPR on hub
- **Package detection** — camera at door detects box left → alert
- **Glass break frequency detection** using microphone + FFT analysis on ESP32

### 5.8 Additional Comfort Features
- **Bed occupancy sensor** using FSR (Force Sensitive Resistor) or mmWave → auto night light, sleep tracking
- **Toilet auto flush** (solenoid valve + PIR — optional, tenant approval needed)
- **Mirror defogger** control in bathroom (relay + humidity sensor)
- **Shoe rack UV deodorizer** (UV-C + timer + PIR interlock)

### 5.9 Network & Infrastructure
- **WiFi mesh** using old routers flashed with OpenWRT + batman-adv or cheap Tenda/Mercusys mesh units
- **Separate IoT VLAN** — isolate automation devices from personal devices (security)
- **Local DNS** (AdGuard Home or Pi-hole on hub) → block ads, faster browsing, device naming
- **Network UPS** — old router + hub on UPS for 2–4 hours outage coverage

### 5.10 Data Privacy & Security
- **No cloud accounts required** for core functionality
- **MQTT over TLS** (optional but recommended for remote access)
- **Home Assistant user roles** — admin vs. family vs. guest
- **No cameras in private areas** (bedroom/bathroom) — mmWave only for fall detection
- **Local NVR** (Network Video Recorder) using Frigate on old PC — AI person detection, no cloud
- **Encrypted backups** to external USB drive — weekly automated

---

## 6. System Architecture at a Glance

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                              INTERNET (Optional)                            │
│                    Tailscale VPN / Cloudflare Tunnel                        │
└─────────────────────────────────────────────────────────────────────────────┘
                                      │
                                      ▼
┌─────────────────────────────────────────────────────────────────────────────┐
│                         OLD PC / LAPTOP (HUB)                               │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐   │
│  │ Home Assistant│  │  Mosquitto   │  │   Node-RED   │  │   Frigate    │   │
│  │   (Docker)   │  │    MQTT      │  │ (Automations)│  │   (NVR/AI)   │   │
│  │  Core + UI   │  │    Broker    │  │   Logic Flow │  │Person Detect │   │
│  └──────────────┘  └──────────────┘  └──────────────┘  └──────────────┘   │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐                      │
│  │   AdGuard    │  │   Wyoming    │  │   InfluxDB   │                      │
│  │   DNS/Block  │  │Voice (Piper+ │  │  (Metrics)   │                      │
│  │              │  │  Whisper)    │  │              │                      │
│  └──────────────┘  └──────────────┘  └──────────────┘                      │
└─────────────────────────────────────────────────────────────────────────────┘
                                      │
                    ┌─────────────────┼─────────────────┐
                    │                 │                 │
                    ▼                 ▼                 ▼
           ┌─────────────┐   ┌─────────────┐   ┌─────────────┐
           │  WiFi AP    │   │  WiFi AP    │   │  WiFi AP    │
           │ (Main Router│   │(Old Router  │   │(Old Router  │
           │  + OpenWRT) │   │  Repeater)  │   │  Repeater)  │
           └─────────────┘   └─────────────┘   └─────────────┘
                    │                 │                 │
        ┌───────────┼───────────┐   │   ┌─────────────┼─────────────┐
        │           │           │   │   │             │             │
        ▼           ▼           ▼   ▼   ▼             ▼             ▼
   ┌────────┐ ┌────────┐ ┌────────┐ ┌────────┐ ┌────────┐ ┌────────┐
   │ ESP32  │ │ ESP32  │ │ ESP32  │ │ ESP32  │ │ ESP32  │ │ ESP8266│
   │ Node 1 │ │ Node 2 │ │ Node 3 │ │ Node 4 │ │ Node 5 │ │ Node 6 │
   │Garden  │ │Kitchen │ │ Water  │ │ Living │ │Security│ │ Aquarium│
   │Sensors │ │ Safety │ │  Pump  │ │ Comfort│ │ Camera │ │ Control│
   └────────┘ └────────┘ └────────┘ └────────┘ └────────┘ └────────┘
        │           │           │        │        │           │
        ▼           ▼           ▼        ▼        ▼           ▼
   [Sensors]  [Sensors]  [Sensors] [Sensors][Camera]   [Sensors]
   [Actuators][Actuators][Actuators][Actuators][IR LEDs][Actuators]
```

### Communication Protocol Stack
| Layer | Technology | Purpose |
|-------|------------|---------|
| **Physical** | WiFi 2.4GHz (802.11n) | Primary connectivity |
| **Network** | TCP/IP | Standard networking |
| **Transport** | MQTT over TCP | Lightweight pub/sub messaging |
| **Application** | ESPHome native API | Device discovery & control |
| **Automation** | Node-RED + HA Automations | Complex logic & scenes |
| **Presentation** | Home Assistant Lovelace | Dashboard & mobile UI |

---

## 7. Documentation Suite Index

This project is documented across **18 comprehensive files**. Each file is designed to be standalone yet cross-referenced.

| # | Filename | Purpose | Target Reader |
|---|----------|---------|---------------|
| 00 | `00_Project_Master_Plan.md` | This file. Vision, scope, roadmap, architecture overview. | You / Investors / Team |
| 01 | `01_System_Architecture_and_Hub_Setup.md` | Old PC setup, Docker, Home Assistant, MQTT, network design, WiFi mesh, VLANs. | System Admin / You |
| 02 | `02_Node_Clubbing_BOM_and_Cost.md` | Which sensors go on which ESP32. Complete BOM per node. Total cost. | Procurement / You |
| 03 | `03_Scrap_Reuse_Guide.md` | How to repurpose old smartphones, PCs, ATX PSUs, routers, speakers, webcams. | You / Cost-conscious builders |
| 04 | `04_Simulation_Guide_Wokwi.md` | Step-by-step Wokwi simulation for every node type. Links and instructions. | You / Learners |
| 05 | `05_Sensor_Actuator_Specifications.md` | Datasheet summaries, pinouts, voltage levels, communication protocols for every component. | Engineer / You |
| 06 | `06_ESPHome_YAML_Configurations_All_Nodes.md` | Complete, commented ESPHome YAML for all 12+ node types. Tuning guide inline. | Firmware Developer / You |
| 07 | `07_Home_Assistant_Configuration_and_Dashboard.md` | HA installation, Lovelace dashboard YAML, entity configuration, mobile app setup. | You / End User |
| 08 | `08_Node_RED_Automations.md` | Node-RED flow exports (JSON), safety automation logic, scene definitions. | Automation Engineer / You |
| 09 | `09_Safety_Guidelines.md` | Electrical safety, gas safety, water safety, fire safety, emergency procedures. | Everyone — **MANDATORY READ** |
| 10 | `10_Procurement_India_Links.md` | Component-by-component Indian vendor links, alternatives, local market tips. | Procurement / You |
| 11 | `11_Testing_Checklist.md` | Pre-commissioning, commissioning, and 30-day burn-in checklists per node and system. | QA / You |
| 12 | `12_DIY_vs_ReadyMade_Recommendations.md` | For each automation: build vs. buy analysis, cost comparison, when to buy off-the-shelf. | You / Commercialization team |
| 13 | `13_Cost_Estimate_Summary.md` | Detailed cost breakdown: prototype, per-node, total system, commercial variant. | Finance / You |
| 14 | `14_Commercialization_PCB_Design_and_Selling.md` | EasyEDA → JLCPCB workflow, enclosure design, pricing strategy, marketing, legal. | Business / You |
| 15 | `15_README_For_Each_Node.md` | Individual README templates for every node type — tuning, troubleshooting, logic. | Installer / End User |
| 16 | `16_Learning_Path_and_References.md` | ELI5 explanations for every automation. Learning resources. Community links. | Beginners / You |
| 17 | `17_GitHub_Repository_Structure_and_README.md` | Folder structure, file naming conventions, contribution guide, license, main README. | Contributors / You |

---

## 8. Build Phases & Timeline

### Phase 1: Foundation (Weeks 1–2)
- [ ] Procure old PC/laptop, verify it boots, install Ubuntu Server LTS
- [ ] Install Docker, Portainer, Home Assistant Container, Mosquitto, Node-RED
- [ ] Set up WiFi network — main router + at least one old router as repeater
- [ ] Set up development environment: VS Code, ESPHome add-on, Git
- [ ] Order common components: 10x ESP32 DevKit, breadboards, jumper wires, DHT22, relays, PIRs
- [ ] Create GitHub repository with folder structure

### Phase 2: Simulation & Firmware (Weeks 3–4)
- [ ] Build Wokwi simulations for: sensor node, relay node, safety node, camera node
- [ ] Write ESPHome YAML for all node types
- [ ] Flash and test 3 "hello world" nodes on breadboard
- [ ] Verify MQTT communication with Home Assistant
- [ ] Build basic Lovelace dashboard

### Phase 3: Safety-Critical Nodes First (Weeks 5–7)
- [ ] **Kitchen Gas Safety Node** — highest priority, lives depend on it
- [ ] **Water Tank / Pump Node** — prevents flooding and dry-run damage
- [ ] **Electrical Monitoring Node** — prevents fire
- [ ] **Fire/Smoke Nodes** — one per floor minimum
- [ ] Test each for 1 week continuous operation before declaring done

### Phase 4: Comfort & Convenience (Weeks 8–10)
- [ ] Living room comfort node (lights, climate)
- [ ] Bedroom nodes
- [ ] Bathroom nodes
- [ ] Garden/balcony nodes
- [ ] Curtain automation

### Phase 5: Security & Monitoring (Weeks 11–12)
- [ ] ESP32-CAM night camera
- [ ] Video doorbell
- [ ] Intrusion alarm system
- [ ] Mobile guard robot (optional, can be Phase 6)

### Phase 6: Specialized Systems (Weeks 13–14)
- [ ] Aquarium automation
- [ ] Air quality monitoring
- [ ] Robot vacuum integration
- [ ] Voice control setup

### Phase 7: Integration & Hardening (Weeks 15–16)
- [ ] Node-RED complex automations and scenes
- [ ] Tailscale/Cloudflare remote access
- [ ] UPS/power backup for critical nodes
- [ ] 30-day continuous burn-in test
- [ ] Family/tenant usability testing
- [ ] Documentation finalization

### Phase 8: Commercialization Prep (Month 5+)
- [ ] Custom PCB design in EasyEDA
- [ ] JLCPCB prototype order
- [ ] Enclosure design and 3D printing
- [ ] Cost optimization pass
- [ ] Pilot installation #1 (friend/family home)

---

## 9. Risk Assessment & Mitigation

| Risk | Probability | Impact | Mitigation |
|------|-------------|--------|------------|
| **WiFi instability** | High | High | Mesh network, MQTT QoS 1, local fallback logic on nodes, ESP32 watchdog timers |
| **False alarms (gas/smoke)** | Medium | High | Dual-sensor validation, 30-second confirmation delay, manual reset required |
| **Power failure** | High | Medium | UPS for hub + critical nodes, battery-backed nodes for security, relay failsafe positions |
| **Sensor drift** | Medium | Medium | Weekly calibration reminders, redundant sensors, threshold tuning via dashboard |
| **Water damage to electronics** | Medium | High | IP65 enclosures, elevated mounting, drip loops on cables, GFCI protection |
| **ESP32 flash corruption** | Low | Medium | OTA updates with rollback, external watchdog, redundant config storage |
| **Tenant damage/rejection** | Medium | Medium | Reversible installation, clear labeling, tenant manual, damage deposit clause |
| **Commercialization delays** | Medium | Low | Parallel track: perfect prototype first, commercialization second, no premature scaling |
| **Component supply issues** | Medium | Medium | Dual-source procurement, standardize on common parts, 20% spare inventory |
| **Electrical shock/fire** | Low | Critical | Follow File 09 religiously, certified components only, fuse every circuit, third-party inspection |

---

## 10. Budget Overview

### Prototype Budget (2-Floor Flat)

| Category | Estimated Cost (₹) | Notes |
|----------|-------------------|-------|
| **ESP32/ESP8266 Nodes** (15 units) | ₹4,500 | ESP32 DevKit v1 @ ₹300 each |
| **Sensors** (all types) | ₹8,000 | Moisture, PIR, gas, smoke, DHT22, ultrasonic, current, etc. |
| **Actuators** (relays, valves, motors) | ₹6,000 | Certified relays, solenoids, contactors, servo/stepper |
| **Power Supplies & Distribution** | ₹3,000 | ATX reuse + 12V/5V adapters, terminal blocks, fuses |
| **Enclosures & Mounting** | ₹2,500 | IP65 boxes, DIN rail, cable glands, magnetic mounts |
| **Cables & Connectors** | ₹2,000 | Jumper wires, Dupont, terminal connectors, heat shrink |
| **Old PC/Laptop** | ₹0 | Reuse existing |
| **Old Routers/Smartphones** | ₹0 | Reuse existing |
| **Safety-Critical Certified Parts** | ₹5,000 | Gas valve, contactors, GFCI, fire-rated enclosures |
| **Spares & Consumables** | ₹2,000 | 20% extra components, solder, flux, wire |
| **3D Printing / Enclosure** | ₹1,000 | Local maker space or own printer |
| **Miscellaneous** | ₹1,000 | Screws, tape, labels, zip ties |
| **TOTAL** | **₹35,000** | **~US$420** |

### Commercial Kit Target Cost (at 100+ unit scale)

| Item | Target Cost (₹) |
|------|----------------|
| Custom PCB + components | ₹800–₹1,200 per node |
| Enclosure (injection molded) | ₹300–₹500 per node |
| Pre-flashed ESP32 module | ₹250–₹350 |
| Sensors (bulk) | ₹400–₹600 per kit |
| Actuators (bulk) | ₹500–₹800 per kit |
| Power supply (shared) | ₹200–₹300 per home |
| Packaging & docs | ₹200–₹300 |
| **Total Kit Cost** | **₹18,000–₹25,000** |
| **Target Selling Price** | **₹45,000–₹65,000** |
| **Gross Margin** | **60%+** |

---

## 11. Success Criteria & KPIs

### Technical KPIs
- [ ] **Uptime:** Hub >99%, critical nodes >99.5% over 30 days
- [ ] **Latency:** Sensor → Action <2 seconds for safety systems
- [ ] **False Alarm Rate:** <1 per week for gas/smoke (tunable thresholds)
- [ ] **OTA Success Rate:** >95% firmware updates without manual intervention
- [ ] **WiFi Coverage:** >-65 dBm signal strength on both floors

### Usability KPIs
- [ ] **Family Approval:** All residents use dashboard weekly without prompting
- [ ] **Mobile Alert Response:** Critical alerts acknowledged <5 minutes
- [ ] **Scene Usage:** At least 3 scenes used daily (Morning/Night/Away)

### Commercial KPIs
- [ ] **Cost per Node:** Reduced 20% from prototype to PCB version
- [ ] **Install Time:** Complete system installed in <8 hours by one person
- [ ] **Support Tickets:** <2 per month per installation after first month
- [ ] **Customer Satisfaction:** NPS >50 after 3 months of use

---

## 12. Next Steps

1. **Read File 09 (Safety Guidelines) FIRST** — before touching any wire
2. **Set up the hub** per File 01 — get Home Assistant running on your old PC
3. **Order Phase 1 components** per File 10 — common parts for first 3 nodes
4. **Simulate your first node** per File 04 — start with a simple PIR light
5. **Build and test** — one node at a time, verify, then move to next
6. **Document as you go** — update YAML comments, take photos, write learnings

---

## Appendices

### A. Glossary of Terms
| Term | Meaning |
|------|---------|
| **ESPHome** | Open-source firmware framework for ESP8266/ESP32. Uses YAML configuration. |
| **MQTT** | Lightweight messaging protocol for IoT. Pub/sub model. |
| **Node-RED** | Visual programming tool for wiring together hardware, APIs, services. |
| **Home Assistant** | Open-source home automation platform. Central brain of the system. |
| **Wokwi** | Online ESP32/Arduino simulator. Test code without hardware. |
| **BOM** | Bill of Materials — list of all components needed. |
| **OTA** | Over-The-Air firmware updates. |
| **DIN Rail** | Standard metal rail for mounting electrical components. |
| **GFCI/ELCB** | Ground Fault Circuit Interrupter / Earth Leakage Circuit Breaker. |
| **Snubber** | Circuit to suppress voltage spikes when relays switch inductive loads. |

### B. Standard Node Naming Convention
```
[zone]_[location]_[function]_[id]
Examples:
  - garden_balcony_water_01
  - kitchen_gas_safety_01
  - living_room_climate_01
  - bedroom_master_light_01
  - security_front_camera_01
  - water_tank_overhead_01
```

### C. File Version Control
All files in this project use Git for version control. Commit message format:
```
[ZONE] Brief description
Example: [KITCHEN] Updated gas threshold from 300 to 500 ppm
```

### D. Emergency Contacts Template
Fill this out and keep printed copy near main electrical panel:
```
Electrician: _______________ Phone: _______________
Plumber: _______________ Phone: _______________
Gas Agency: _______________ Phone: _______________
Fire Department: 101
Ambulance: 102 / 108
Police: 100
Home Assistant Remote Access: _______________
```

---

> **"The best automation is the one you forget exists — until it saves your home."**
>
> Build safe. Build local. Build to last.

---
*End of 00_Project_Master_Plan.md*
*Next: 01_System_Architecture_and_Hub_Setup.md*
