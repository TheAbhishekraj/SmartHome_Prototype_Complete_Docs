# 📖 The SmartHome Bible — Complete Project Index & Navigation Guide

**Version:** 1.0 | **Date:** August 2026  
**Purpose:** One document to rule them all. Read this first. Bookmark it. Come back to it whenever you're lost.

---

## 🗺️ How to Use This Bible

| If you want to... | Go to... |
|-------------------|----------|
| **Understand the big picture** | Section 1: Project Overview |
| **Know what each file contains** | Section 2: The 18-File Map |
| **Decide where to start building** | Section 3: Build Order & Reading Path |
| **Understand how files connect** | Section 4: File Relationships & Cross-References |
| **Learn key terms** | Section 5: Concept Dictionary |
| **Fix a problem** | Section 6: Troubleshooting Index |
| **Explain the project to someone** | Section 7: Elevator Pitches |
| **Plan commercialization** | Section 8: Business Roadmap at a Glance |

---

## 1. Project Overview (The Big Picture)

### What Are We Building?
A **complete smart home brain** for a 2-floor apartment that:
- Waters your plants automatically
- Detects gas leaks before they explode
- Fills your water tank without burning the pump
- Turns lights on when you walk in, off when you leave
- Watches your door with cameras
- Feeds your fish
- Monitors your electricity
- Calls your phone if anything goes wrong

**All without sending your data to Google, Amazon, or any company.**

### The Three Layers

```
┌─────────────────────────────────────────────────────────────┐
│  LAYER 1: YOU (Phone, Dashboard, Voice)                     │
│  → Home Assistant app, wall tablet, voice commands          │
├─────────────────────────────────────────────────────────────┤
│  LAYER 2: THE BRAIN (Old PC/Laptop)                        │
│  → Home Assistant + Mosquitto MQTT + Node-RED + Frigate      │
│  → Runs 24/7 on your old computer                          │
├─────────────────────────────────────────────────────────────┤
│  LAYER 3: THE NERVES (ESP32/ESP8266 chips)                │
│  → 15+ small computers hidden around your home             │
│  → Each has sensors (eyes) and relays (hands)              │
│  → Talk to the brain via WiFi + MQTT                       │
└─────────────────────────────────────────────────────────────┘
```

### The Philosophy
| Principle | What It Means |
|-----------|---------------|
| **Safety First** | New certified parts for gas, water, and mains electricity. No compromises. |
| **Scrap Reuse** | Old laptop = brain. Old phone = wall dashboard. Old router = WiFi repeater. Old PSU = power supply. |
| **Local Control** | Your data never leaves your home. Internet is optional. |
| **Simulation First** | Test every circuit in Wokwi (free online simulator) before touching real wires. |
| **Modular** | One node breaks? Swap it in 5 minutes. The rest of the house keeps working. |
| **Tenant Friendly** | No drilling walls. Command strips, magnetic mounts, existing switch boxes. |

---

## 2. The 18-File Map

Think of these 18 files as chapters in a technical manual. Each has a specific purpose and audience.

### 🔴 START HERE (Read Before Anything Else)

#### File 00 — `00_Project_Master_Plan.md`
**What it is:** The CEO's briefing document. The 30,000-foot view.
**What's inside:**
- Vision and commercialization goals (5 phases over 24 months)
- Complete scope: 8 zones, 40+ automations
- 10 expert additions (energy monitoring, voice control, predictive maintenance, etc.)
- System architecture diagram
- Budget overview (₹37,500 prototype vs ₹55,000 selling price)
- Risk assessment table
- Success criteria and KPIs
**Who should read:** Everyone. Especially you, investors, and anyone joining your team.
**When to read:** Before buying a single component.
**Key takeaway:** "This is possible, this is affordable, and this can become a business."

#### File 09 — `09_Safety_Guidelines.md`
**What it is:** The document that keeps you alive.
**What's inside:**
- Electrical safety rules for 230V AC
- Gas sensor placement (LPG sinks, natural gas rises)
- Water valve and leak safety
- Fire safety and sensor placement
- Battery (Li-ion) handling
- Emergency procedures (shock, gas leak, fire)
- Compliance with Indian electrical codes
- Safety checklist before powering on
**Who should read:** Everyone who touches a wire.
**When to read:** BEFORE File 01. Before any hardware.
**Key takeaway:** "A ₹50 component is not worth a hospital visit."

---

### 🟡 THE FOUNDATION (Build the Brain First)

#### File 01 — `01_System_Architecture_and_Hub_Setup.md`
**What it is:** How to turn your old laptop into the home's brain.
**What's inside:**
- Old PC requirements and preparation
- Ubuntu Server installation
- Docker + Docker Compose setup
- Home Assistant, Mosquitto MQTT, Node-RED, Frigate, InfluxDB, AdGuard containers
- Network architecture diagram
- WiFi mesh using old routers (OpenWRT)
- IoT VLAN isolation (security)
- Remote access: Tailscale VPN + Cloudflare Tunnel
- Backup strategy
- Power backup / UPS
- IP addressing scheme for all devices
**Who should read:** You, any system administrator.
**When to read:** After safety, before buying sensors.
**Key takeaway:** "Your old laptop becomes a professional-grade automation server for ₹0."

---

### 🟢 THE HARDWARE (What to Buy & Where)

#### File 02 — `02_Node_Clubbing_BOM_and_Cost.md`
**What it is:** The complete shopping list. Every resistor, every wire, every screw.
**What's inside:**
- Physical node map for both floors (where each ESP32 goes)
- Node-by-node BOM (Bill of Materials) with Indian prices
- 20 nodes total, ₹37,500 grand total
- Common components shared across nodes
- Node placement guidelines (where to mount, how to mount)
- Cable and power distribution plan
**Who should read:** You, anyone doing procurement.
**When to read:** After hub setup, before ordering.
**Key takeaway:** "One ESP32 per zone, not one per sensor. Saves 60% cost."

#### File 10 — `10_Procurement_India_Links.md`
**What it is:** Where to buy everything in India.
**What's inside:**
- Online vendors (Robu.in, ElectronicsComp, Amazon.in, Thingbits, Sunrom, Flyrobo, DigiKey, Mouser)
- Search terms for each component
- Local market guide (Lajpat Rai Delhi, SP Road Bangalore, Lamington Road Mumbai, etc.)
- Local market tips (bargaining, testing, ISI marks)
**Who should read:** You, procurement person.
**When to read:** When you're ready to order parts.
**Key takeaway:** "SP Road Bangalore has everything. Carry a list and test before buying."

#### File 03 — `03_Scrap_Reuse_Guide.md`
**What it is:** How to turn trash into automation gold.
**What's inside:**
- Old PC/laptop → Home Assistant hub
- ATX power supply → 5V/12V DC rail for all nodes
- Old smartphones → Wall dashboards, NFC readers, IP cameras
- Old WiFi routers → Mesh access points (OpenWRT flashing guide)
- Old speakers → Smart announcement system
- Old webcams → IP cameras via MotionEye
- Old laptop batteries → 18650 cell harvesting (with safety warnings)
- Old USB cables/chargers → Power distribution
- What NOT to reuse (mains relays, gas valves, smoke sensors)
- Scrap reuse summary table (₹22,500–₹48,000 saved)
**Who should read:** You, anyone who hates e-waste.
**When to read:** Before ordering — check what you already have.
**Key takeaway:** "The best component is the one you already own."

---

### 🔵 THE KNOWLEDGE (Understand Before Building)

#### File 05 — `05_Sensor_Actuator_Specifications.md`
**What it is:** The datasheet cheat sheet. Every sensor and actuator explained.
**What's inside:**
- ESP32 DevKit v1 pinout and specs
- ESP8266 NodeMCU specs
- ESP32-CAM specs and available pins
- Temperature sensors: DHT22, BME280, DS18B20
- Motion sensors: HC-SR501, AM312
- Gas/smoke: MQ-6, MQ-2, optical smoke
- Water: capacitive soil moisture, leak sensors, float switches
- Distance: HC-SR04, JSN-SR04T
- Current/power: ACS712, PZEM-004T
- Air quality: PMS5003, MH-Z19B, CCS811
- mmWave radar: LD2410B
- Relays, contactors, solenoid valves, stepper motors, servos
- Quick reference pinout table
**Who should read:** You, any engineer building nodes.
**When to read:** Before soldering. Keep open while wiring.
**Key takeaway:** "GPIO 34-39 are input-only and best for analog sensors."

#### File 04 — `04_Simulation_Guide_Wokwi.md`
**What it is:** Test your circuits without burning anything.
**What's inside:**
- 10 complete Wokwi simulations with circuit diagrams and code
- PIR motion light, DHT22 climate control, soil moisture + pump
- Gas leak detection, ultrasonic tank level, ESP32-CAM
- Stepper motor curtain, ACS712 current monitoring, IR blaster, reed switch
- How to test MQTT payloads in simulation
- Tinkercad as alternative
**Who should read:** You, any beginner.
**When to read:** Before buying parts for each node.
**Key takeaway:** "Every node MUST be simulated before breadboard testing."

---

### 🟣 THE SOFTWARE (The Soul of the System)

#### File 06 — `06_ESPHome_YAML_Configurations_All_Nodes.md`
**What it is:** The firmware. Complete ESPHome YAML for all 15+ node types.
**What's inside:**
- YAML basics and tuning guide
- NODE-A1: Garden controller (soil moisture ×3, rain, light, PIR, valves, awning motor)
- NODE-B1: Kitchen safety (MQ-6 gas, MQ-2 smoke, DHT22, leak, exhaust, gas valve, siren)
- NODE-C1: Water tank & pump (float switches ×5, ultrasonic, ACS712, contactor)
- NODE-D1: Living room comfort (PIR ×2, LDR, DHT22, reed switches, light, IR blaster, curtain stepper)
- NODE-E1: Master bathroom (DHT22, PIR, leak, DS18B20, exhaust, geyser, water valve)
- NODE-F1: Night security camera (ESP32-CAM, PIR, IR LEDs, SD storage)
- NODE-F3: Intrusion alarm (reed switches ×4, PIR ×2, glass break, siren)
- NODE-G2: Air quality (PMS5003, MH-Z19B, CCS811, ventilation)
- NODE-H1: Aquarium (DS18B20, float, TDS, heater, light, filter, servo feeder, top-up pump)
- NODE-S1: Electrical monitor (PZEM-004T, emergency contactor)
- NODE-S3: Panic button (battery-powered, deep sleep)
- NODE-S5: Fire detection (smoke sensor, buzzer)
- Common substitutions table (what to use if you don't have exact part)
- OTA troubleshooting
**Who should read:** You, firmware developer.
**When to read:** After simulation, during physical build.
**Key takeaway:** "All tunable values are marked with # TUNE: comments."

#### File 07 — `07_Home_Assistant_Configuration_and_Dashboard.md`
**What it is:** The pretty screen you look at. And the rules behind it.
**What's inside:**
- Initial HA setup steps
- Core integrations (MQTT, ESPHome, Sun, Mobile App)
- Complete Lovelace dashboard YAML (8 views: Overview, Climate, Lights, Water, Garden, Cameras, Aquarium, Scenes)
- Scene definitions (Morning, Night, Away, Party, Movie)
- Mobile app setup
- Notification scripts (panic, gas, smoke, water, dry run)
- Basic automations (morning routine, night routine, auto-away, auto-home)
- Entity organization and groups
- Backup and restore procedures
**Who should read:** You, end user, family members.
**When to read:** After nodes are flashed and connected.
**Key takeaway:** "One dashboard controls everything. Your phone becomes the remote for your entire home."

#### File 08 — `08_Node_RED_Automations.md`
**What it is:** The smart logic that HA can't do easily. Visual programming.
**What's inside:**
- Node-RED setup and essential nodes
- Flow 1: Gas leak emergency sequence (escalation after 30 seconds)
- Flow 2: Intrusion alarm logic (entry delay, instant triggers)
- Flow 3: Water tank smart pump control (dry-run protection)
- Flow 4: Scene controller (complex conditional scenes)
- Flow 5: Predictive maintenance (trend analysis)
- Flow 6: Energy peak load management (load shedding)
- Flow 7: Voice command handler (local voice control)
- Flow 8: Telegram bot alerts (backup notification channel)
- Flow export/import guide for version control
**Who should read:** You, automation engineer.
**When to read:** After HA dashboard is working.
**Key takeaway:** "Node-RED handles the complex 'if-this-then-that' logic that would be messy in HA YAML."

---

### 🟠 THE PROCESS (How to Build & Test)

#### File 11 — `11_Testing_Checklist.md`
**What it is:** Don't guess. Check every box.
**What's inside:**
- Phase 1: Pre-commissioning (hub, per-node bench testing)
- Phase 2: Installation testing (electrical safety, node-by-node)
- Phase 3: System integration (communication, automation, safety end-to-end, stress testing)
- Phase 4: 30-day burn-in (daily/weekly checks, sign-off criteria)
**Who should read:** You, QA person.
**When to read:** During and after installation.
**Key takeaway:** "A system that hasn't been tested is a system that will fail at 2 AM."

#### File 12 — `12_DIY_vs_ReadyMade_Recommendations.md`
**What it is:** Should you build it or buy it? The honest answer.
**What's inside:**
- Decision matrix for all 16 automation types
- When to DIY (cost savings >60%, simple, non-life-critical)
- When to buy (life safety, insurance requires, warranty needed)
- Hybrid approach table (DIY sensor + certified actuator)
**Who should read:** You, anyone deciding what to build.
**When to read:** During planning phase.
**Key takeaway:** "DIY the brain, buy the certified safety parts."

---

### 🟤 THE BUSINESS (From Hobby to Product)

#### File 13 — `13_Cost_Estimate_Summary.md`
**What it is:** The money document. Every rupee accounted for.
**What's inside:**
- Prototype cost breakdown (₹37,500 total)
- Cost per zone
- Commercial kit cost projection (₹22,000 cost, ₹55,000 selling price, 60% margin)
- Scaling economics (10/50/100/500 units)
**Who should read:** You, investors, business partner.
**When to read:** When planning budget or pitching.
**Key takeaway:** "60% gross margin at scale. ₹55,000 vs ₹2,00,000 commercial alternative."

#### File 14 — `14_Commercialization_PCB_Design_and_Selling.md`
**What it is:** From breadboard to business.
**What's inside:**
- Phase 1: PCB design in EasyEDA → JLCPCB ordering
- Phase 2: Branded kit (3 tiers: Lite/Pro/Elite)
- Phase 3: Scaling (manufacturing partnership, sales channels, marketing)
- Legal & compliance (GST, BIS, liability insurance)
**Who should read:** You, future business owner.
**When to read:** After prototype is working and reliable.
**Key takeaway:** "Start with 10 pilot installations, then scale."

---

### ⚪ THE DOCUMENTATION (For Future You & Others)

#### File 15 — `15_README_For_Each_Node.md`
**What it is:** A template for documenting every node you build.
**What's inside:**
- README template (what it does, sensors, actuators, thresholds, timing, logic, safety, troubleshooting, wiring)
- Example: NODE-B1 Kitchen Safety complete README
**Who should read:** You, future maintainer, anyone inheriting the project.
**When to read:** After building each node, fill out one README per node.
**Key takeaway:** "Future-you will thank present-you for good documentation."

#### File 16 — `16_Learning_Path_and_References.md`
**What it is:** The textbook. Learn everything from zero.
**What's inside:**
- 6-week learning path (foundations → sensors → actuators → communication → integration → safety)
- ELI5 explanations for every automation (garden, kitchen gas, water tank, motion lights, camera, alarm, aquarium, electrical monitor)
- Reference links (ESPHome docs, HA docs, tutorials, safety standards)
**Who should read:** Beginners, you when you forget how something works.
**When to read:** Before starting, and whenever stuck.
**Key takeaway:** "You don't need an engineering degree. You need curiosity and patience."

#### File 17 — `17_GitHub_Repository_Structure_and_README.md`
**What it is:** How to organize everything on GitHub.
**What's inside:**
- Complete folder structure (docs, firmware, homeassistant, nodered, pcb, simulations, photos, videos, tools)
- .gitignore template
- MIT License with safety disclaimer
- Main README.md template with badges and quick-start
**Who should read:** You, contributors.
**When to read:** When uploading to GitHub.
**Key takeaway:** "Organized code is shareable code."

---

## 3. Build Order & Reading Path

### 📚 If You're a Beginner (Never touched ESP32 before)

```
WEEK 1:
  Day 1 → Read File 00 (Master Plan) — understand the vision
  Day 2 → Read File 09 (Safety) — understand the dangers
  Day 3 → Read File 16 (Learning Path) — start Week 1 lessons
  Day 4-7 → Blink LED on ESP32, read DHT22, control relay

WEEK 2:
  Day 1 → Read File 01 (Hub Setup) — install Ubuntu on old PC
  Day 2-3 → Set up Docker, Home Assistant, MQTT
  Day 4 → Read File 04 (Simulation) — build first Wokwi circuit
  Day 5-7 → Read File 05 (Sensor Specs) — understand your components

WEEK 3:
  Day 1 → Read File 02 (BOM) — order first 3 nodes worth of parts
  Day 2 → Read File 10 (Procurement) — place orders
  Day 3 → Read File 03 (Scrap Reuse) — gather old electronics
  Day 4-7 → Simulate kitchen safety node in Wokwi

WEEK 4:
  Day 1-3 → Build kitchen safety node on breadboard
  Day 4 → Flash File 06 YAML, test with HA
  Day 5-7 → Build water tank node

WEEK 5-8:
  Build remaining nodes one by one
  Check File 11 (Testing) after each node

WEEK 9-12:
  Set up dashboard (File 07)
  Build Node-RED flows (File 08)
  30-day burn-in (File 11)
```

### 🚀 If You Already Know ESP32 & Home Assistant

```
DAY 1:
  Read File 00 (Master Plan) — 30 minutes
  Read File 09 (Safety) — 30 minutes
  Read File 02 (BOM) — 1 hour
  Order parts (File 10) — 2 hours

DAY 2:
  Set up hub (File 01) — 4 hours
  Configure HA + MQTT (File 07) — 2 hours

DAY 3-7:
  Simulate all nodes (File 04) — 1 day
  Flash YAML for all nodes (File 06) — 2 days
  Install physically — 2 days

DAY 8-10:
  Test everything (File 11)
  Set up Node-RED (File 08)
  Configure dashboard (File 07)

DAY 11+:
  30-day burn-in
  Start commercialization planning (Files 13-14)
```

---

## 4. File Relationships & Cross-References

### The Dependency Web

```
File 00 (Master Plan)
    ├── File 01 (Hub Setup) ──→ File 07 (HA Dashboard)
    │                              └── File 08 (Node-RED)
    ├── File 02 (BOM) ────────→ File 10 (Procurement)
    │       └── File 03 (Scrap Reuse)
    ├── File 04 (Simulation) ──→ File 06 (ESPHome YAML)
    │       └── File 05 (Sensor Specs)
    ├── File 06 (YAML) ────────→ File 07 (Dashboard)
    │                              └── File 15 (Node READMEs)
    ├── File 09 (Safety) ──────→ EVERYTHING
    ├── File 11 (Testing) ─────→ File 06, 07, 08
    ├── File 12 (DIY vs Buy) ──→ File 02 (BOM)
    ├── File 13 (Cost) ────────→ File 02 (BOM), File 14 (Commercial)
    └── File 14 (Commercial) ──→ File 17 (GitHub)
```

### How Files Talk to Each Other

| When you're in... | You need to also look at... | Why |
|-------------------|----------------------------|-----|
| File 02 (BOM) | File 05 (Sensor Specs) | To confirm pin compatibility |
| File 02 (BOM) | File 03 (Scrap Reuse) | To mark what you already have |
| File 04 (Simulation) | File 06 (YAML) | Simulation logic becomes YAML |
| File 06 (YAML) | File 05 (Sensor Specs) | Pin numbers, voltage levels |
| File 06 (YAML) | File 09 (Safety) | Fuses, fail-safe design |
| File 07 (Dashboard) | File 06 (YAML) | Entity IDs must match YAML names |
| File 08 (Node-RED) | File 07 (Dashboard) | Events trigger dashboard alerts |
| File 11 (Testing) | File 06 (YAML) | Verify every sensor reads correctly |
| File 14 (Commercial) | File 13 (Cost) | Pricing based on BOM |
| File 15 (Node README) | File 06 (YAML) | Document what you built |

---

## 5. Concept Dictionary (What Does ___ Mean?)

### The Brain (Software Stack)

| Term | Simple Meaning | Where to Learn More |
|------|---------------|---------------------|
| **Home Assistant** | The main app that shows your home's status and controls everything. Like a universal remote for your house. | File 07 |
| **ESPHome** | A tool that turns ESP32 chips into smart devices using simple YAML files. No C++ coding needed. | File 06 |
| **MQTT** | The messenger service. Nodes send sensor data to the brain via MQTT. Brain sends commands back via MQTT. | File 01 |
| **Node-RED** | Visual programming tool. Drag-and-drop boxes to create complex rules. "If motion detected AND it's dark, turn on light." | File 08 |
| **Mosquitto** | The actual software that runs the MQTT messenger service. | File 01 |
| **Frigate** | Smart camera recorder. Uses AI to detect people, not just motion. Keeps video on your hard drive, not cloud. | File 01 |
| **Lovelace** | The name of Home Assistant's dashboard system. You design cards and views. | File 07 |
| **Docker** | A box that lets you run multiple apps (HA, MQTT, Node-RED) on one computer without them fighting. | File 01 |
| **Tailscale** | A magic tunnel that lets you access your home from anywhere securely. Like a private internet for your devices. | File 01 |

### The Nerves (Hardware)

| Term | Simple Meaning | Where to Learn More |
|------|---------------|---------------------|
| **ESP32** | A tiny $3 computer with WiFi. The "helper" that lives in each room. | File 05 |
| **ESP8266** | A cheaper, simpler version of ESP32. Good for simple nodes. | File 05 |
| **GPIO** | The pins on ESP32 that connect to sensors and relays. Like USB ports but for wires. | File 05 |
| **Relay** | An electric switch controlled by ESP32. Turns high-power things (lights, fans) on/off safely. | File 05 |
| **Contactor** | A heavy-duty relay for very high power (pumps, geysers, AC). | File 05 |
| **Solenoid Valve** | An electric tap. When ESP32 sends power, the valve opens or closes. | File 05 |
| **ADC** | Analog-to-Digital Converter. Turns sensor voltage (0-3.3V) into numbers ESP32 understands. | File 05 |
| **I2C / UART** | Ways for ESP32 to talk to sensors. Like different languages devices use. | File 05 |
| **Pull-up Resistor** | A helper resistor that keeps a pin at 3.3V until a sensor pulls it down. Prevents false readings. | File 05 |
| **Snubber** | A small circuit that prevents sparks when relays switch motors. Protects relay contacts. | File 09 |
| **GFCI / ELCB** | A safety switch that cuts power if electricity leaks to ground (like through water or a person). | File 09 |

### The Language (YAML & Code)

| Term | Simple Meaning | Where to Learn More |
|------|---------------|---------------------|
| **YAML** | A simple text format for configuration. Uses indentation (spaces) instead of brackets. | File 06 |
| **Entity ID** | The unique name of every sensor and switch in Home Assistant. Like `sensor.kitchen_temperature`. | File 07 |
| **OTA** | Over-The-Air update. Flash new firmware to ESP32 wirelessly without plugging in a cable. | File 06 |
| **Lambda** | A mini code snippet inside YAML. Lets you do custom math or logic. | File 06 |
| **Hysteresis** | A gap between ON and OFF thresholds. Prevents rapid switching. Example: Fan ON at 28°C, OFF at 26°C. | File 04 |
| **Interlock** | Prevents two dangerous things from happening at once. Example: Don't open gas valve while sparking igniter. | File 06 |
| **Fail-safe** | Design where "power off" equals "safe state." Gas valve CLOSES when power lost. | File 09 |

### The Process

| Term | Simple Meaning | Where to Learn More |
|------|---------------|---------------------|
| **BOM** | Bill of Materials. The shopping list of every component. | File 02 |
| **Wokwi** | Free online simulator. Build virtual ESP32 circuits and test code without real hardware. | File 04 |
| **Burn-in** | Running a new system continuously for days/weeks to find problems before relying on it. | File 11 |
| **Commissioning** | The process of testing and verifying everything works before declaring the project "done." | File 11 |
| **DFM** | Design for Manufacturability. Making your circuit board easy to mass-produce. | File 14 |
| **Gerber** | The file format PCB manufacturers need to make your circuit board. | File 14 |

---

## 6. Troubleshooting Index

### "I don't know where to start"
→ Read this Bible (File Bible), then File 00, then File 09.

### "What parts do I need?"
→ File 02 (BOM) + File 10 (Procurement).

### "How do I set up the hub?"
→ File 01 (Hub Setup).

### "How do I test without buying parts?"
→ File 04 (Simulation).

### "What pin connects to what?"
→ File 05 (Sensor Specs) + File 06 (YAML).

### "How do I write the code?"
→ File 06 (YAML). Copy, paste, tune values marked # TUNE:.

### "How do I make the dashboard?"
→ File 07 (HA Dashboard).

### "How do I set up complex rules?"
→ File 08 (Node-RED).

### "Is this safe?"
→ File 09 (Safety). Read it. Twice.

### "How do I know it works?"
→ File 11 (Testing Checklist).

### "Should I build or buy this part?"
→ File 12 (DIY vs Buy).

### "How much will this cost?"
→ File 13 (Cost Summary).

### "How do I sell this?"
→ File 14 (Commercialization).

### "How do I document what I built?"
→ File 15 (Node README template).

### "I don't understand how X works"
→ File 16 (Learning Path + ELI5).

### "How do I put this on GitHub?"
→ File 17 (GitHub Structure).

---

## 7. Elevator Pitches

### For Your Family
> "I put a small computer in our old laptop that talks to tiny helpers around the house. Now the lights turn on when you walk in, the plants water themselves, and if there's ever a gas leak, the system will close the gas valve and call my phone before anything bad happens."

### For a Friend Who Wants One
> "I built a complete smart home system for ₹37,000 that does everything a ₹2 lakh commercial system does — but your data stays in your home, not on some company's server. Want me to build one for you?"

### For an Investor
> "We're developing a modular, privacy-first smart home kit for the Indian market at 60% gross margin. Prototype complete, 15 nodes, 40+ automations, zero cloud dependency, designed for scalability from ₹55,000 retail price point."

### For an Electrician
> "I'm installing low-voltage automation nodes that control relays and contactors. All mains work is done by certified contactors with proper fuses and GFCI protection. I need you to verify the mains distribution and earth connections."

---

## 8. Business Roadmap at a Glance

| Phase | Timeline | What Happens | Key File |
|-------|----------|-------------|----------|
| **Prototype** | Months 1-3 | Build in your home, use daily, document | Files 00-11 |
| **Refinement** | Months 4-6 | Harden system, reduce cost 20%, OTA pipeline | Files 06, 11 |
| **Custom PCB** | Months 7-9 | EasyEDA → JLCPCB, enclosure design | File 14 |
| **Branded Kit** | Months 10-14 | Packaging, pilot installs, video guides | Files 13-14 |
| **Scaling** | Months 15-24 | Manufacturing, B2B, multi-city | File 14 |

---

## 9. Quick Reference: File Sizes & Complexity

| File | Size | Complexity | Beginner Friendly? |
|------|------|------------|-------------------|
| 00 Master Plan | Large | Medium | ✅ Yes |
| 01 Hub Setup | Large | High | ⚠️ Technical |
| 02 BOM | Large | Medium | ✅ Yes |
| 03 Scrap Reuse | Medium | Low | ✅ Yes |
| 04 Simulation | Large | Medium | ✅ Yes |
| 05 Sensor Specs | Large | High | ⚠️ Technical |
| 06 ESPHome YAML | Very Large | High | ⚠️ Technical |
| 07 HA Dashboard | Large | Medium | ✅ Yes |
| 08 Node-RED | Medium | High | ⚠️ Technical |
| 09 Safety | Medium | Low | ✅ Essential |
| 10 Procurement | Small | Low | ✅ Yes |
| 11 Testing | Medium | Low | ✅ Yes |
| 12 DIY vs Buy | Small | Low | ✅ Yes |
| 13 Cost | Small | Low | ✅ Yes |
| 14 Commercial | Medium | Medium | ✅ Yes |
| 15 Node README | Small | Low | ✅ Yes |
| 16 Learning | Large | Low | ✅ Yes |
| 17 GitHub | Medium | Low | ✅ Yes |

---

## 10. The One-Page Cheat Sheet

### Architecture
```
You (Phone) ←→ Tailscale/Cloudflare ←→ Old PC (HA+MQTT+Node-RED)
                                           ↕ WiFi
                                    ESP32 Nodes (15+)
                                    ├─ Sensors (eyes)
                                    └─ Relays (hands)
```

### Communication Flow
```
Sensor detects something → ESP32 reads it → Sends via MQTT →
Home Assistant records it → Node-RED decides action →
Sends command via MQTT → ESP32 acts (relay on/off)
```

### Build Order
```
1. Read Safety (File 09)
2. Set up Hub (File 01)
3. Order Parts (Files 02, 10)
4. Gather Scrap (File 03)
5. Simulate (File 04)
6. Flash YAML (File 06)
7. Build Dashboard (File 07)
8. Add Logic (File 08)
9. Test Everything (File 11)
10. Document (File 15)
11. Plan Business (Files 13-14)
```

### Emergency Contacts (Fill This In)
```
Electrician: _________________ Phone: _________________
Plumber: ____________________ Phone: _________________
Gas Agency: _________________ Phone: _________________
Fire: 101 | Ambulance: 102/108 | Police: 100
Home Assistant Remote: _____________________________
```

---

> **"This Bible is your map. The 18 files are your territory. Start with safety, build with patience, and document as you go."**

*End of The SmartHome Bible*
