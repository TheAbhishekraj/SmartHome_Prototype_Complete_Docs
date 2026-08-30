# 09_Safety_Guidelines.md
# SmartHome Prototype — Safety Guidelines & Electrical Code Compliance

**Version:** 1.0 | **Date:** August 2026

> ⚠️ **WARNING: This document contains life-safety information. Read completely before starting any work.**

---

## Table of Contents
1. [General Safety Philosophy](#1-general-safety-philosophy)
2. [Electrical Safety (230V AC)](#2-electrical-safety-230v-ac)
3. [Gas Safety (LPG/Natural Gas)](#3-gas-safety-lpgnatural-gas)
4. [Water Safety](#4-water-safety)
5. [Fire Safety](#5-fire-safety)
6. [Chemical Safety (Sensors)](#6-chemical-safety-sensors)
7. [Battery Safety (Li-ion)](#7-battery-safety-li-ion)
8. [Installation Safety](#8-installation-safety)
9. [Emergency Procedures](#9-emergency-procedures)
10. [Compliance & Codes](#10-compliance--codes)
11. [Safety Checklist Before Power-On](#11-safety-checklist-before-power-on)

---

## 1. General Safety Philosophy

**The Three Rules:**
1. **If you are not 100% sure, STOP and ask a professional.**
2. **Safety devices (fuses, GFCI, contactors) are NOT optional.**
3. **Test with multimeter BEFORE touching any wire.**

**Golden Rule of Electricity:**
> "Treat every wire as live until proven otherwise with your own multimeter."

---

## 2. Electrical Safety (230V AC)

### 2.1 Understanding Indian Mains Power
- **Voltage:** 230V AC ±10% (207V–253V)
- **Frequency:** 50 Hz
- **Standard Circuits:** 5A (lighting), 15A (power), 16A/20A (AC/geyser)
- **Wire Colors:**
  - **Red/Blue/Yellow** = Phase (Live) — CARRY VOLTAGE
  - **Black** = Neutral
  - **Green/Yellow** = Earth (Ground) — SAFETY

### 2.2 Before Working on ANY Electrical Circuit
```
□ Turn OFF breaker at main panel
□ Lock out breaker (tape + sign: "DO NOT SWITCH ON")
□ Test with multimeter: Phase-Neutral = 0V, Phase-Earth = 0V
□ Use insulated tools only
□ Wear rubber-soled shoes
□ Work in dry conditions only
□ Have someone nearby who knows where the main breaker is
```

### 2.3 Relay & Contactor Wiring

**CRITICAL RULES:**
- **Always use a fuse** on the load side of any relay switching mains
- **Always use a contactor** (not just relay) for loads >10A (motors, geysers, AC)
- **Always add a snubber circuit** across relay contacts for inductive loads
- **Never exceed relay rating** — if motor draws 12A, use 25A contactor
- **Use NO (Normally Open)** for safety-critical loads — device is OFF when ESP32 is off

**Snubber Circuit (for inductive loads like motors, fans):**
```
Relay Contacts
    ┌───┐
    │   │
   ─┴───┴─
    │   │
    │  [0.1µF capacitor + 100Ω resistor in series]
    │   │
   Load (Motor/Fan)
```

**Fuse Sizing:**
| Load Type | Current Draw | Fuse Rating | Contactor Rating |
|-----------|-------------|-------------|------------------|
| Light (LED) | 0.5A | 2A | 10A relay |
| Exhaust fan | 1-2A | 5A | 10A relay |
| Water pump (0.5HP) | 3-5A | 10A | 16A contactor |
| Geyser (15L) | 8-12A | 16A | 25A contactor |
| AC (1.5 ton) | 6-10A | 16A | 25A contactor |
| Main cutoff | 20-40A | 32A/63A | 40A contactor |

### 2.4 GFCI / ELCB Protection

**GFCI (Ground Fault Circuit Interrupter)** or **ELCB (Earth Leakage Circuit Breaker)** MUST be installed on:
- Any circuit near water (bathroom, kitchen, pump area)
- Any automation circuit sharing space with water pipes
- Aquarium power supply

**How it works:** Detects current leaking to ground (>30mA) and trips in <30ms.

**Test monthly:** Press TEST button, should trip immediately.

### 2.5 Earth/Ground Connection
- **Every metal enclosure** must be earthed
- **Every mains circuit** must have proper earth
- **Earth wire must be continuous** — no breaks, no joints
- **Earth resistance** should be <5Ω (test with earth tester)

### 2.6 Cable Sizing
| Current | Cable Size (Copper) | Application |
|---------|---------------------|-------------|
| <3A | 0.75 mm² | Sensors, 5V DC |
| 3-6A | 1.5 mm² | 12V solenoids, small motors |
| 6-16A | 2.5 mm² | Power outlets, pumps |
| 16-25A | 4.0 mm² | Geysers, AC units |
| 25-40A | 6.0 mm² | Main distribution |

**Use ISI-marked cables only.**

### 2.7 Master Emergency Cutoff — PHYSICAL "ALL-OFF" (Hub-Independent) ⚠️ MANDATORY
A software "OFF" command is **NOT** enough. A hung ESP32 or a dead hub must NEVER leave a pump, gas valve, or load energized and impossible to stop. Install a dedicated **physical master emergency contactor + ALL-OFF switch** that is completely independent of the ESP32/hub / power rail.

**Hardware (new, certified only):**
- 1x mains-rated contactor sized for your main load (e.g. 40A) — the ALL-OFF isolator
- 1x normally-closed (NC) physical kill switch (e.g. mushroom "MAIN OFF") wired in the contactor-coil circuit
- 1x reset button to re-energize after an ALL-OFF (may be combined with the kill switch as a maintained toggle)
- All automated loads (lights, pump, valve, siren, etc.) fed **through** the contactor's main contacts, so opening it drops every automated load at once

**Behavior / Fail-safe:**
- The contactor coil is fed from a **separate supply** (not the ESP32). Pressing ALL-OFF de-energizes the coil → main contacts open → every automated load goes OFF.
- Uses a spring-return / NC design: any coil loss **fails the loads OPEN** (dead device = loads OFF, never stuck ON).
- The physical override always beats software — it works even if the hub is offline or firmware is caught in a loop.

**Installation (licensed electrician must verify before energizing):**
```
┌────────────┐            ┌────────────────────────────────┐
│ Mains IN   │──P───►  [ Contactor main contacts ] ──►  Automated Loads
│ 230V 50Hz  │──N───►   ──────────────────────────────────
└────────────┘            (pump / valve / light / siren)

Contactor coil circuit (SEPARATE small supply, not the ESP32):
  Coil Supply ──► [NC ALL-OFF switch] ──► [Reset switch] ──► Coil ──► Return
       Press ALL-OFF  →  coil de-energised  →  contacts OPEN  →  ALL LOADS OFF
```
- Place the contactor inside/near the main panel; mount the kill button where it is reachable **without opening the panel**, clearly labelled `EMERGENCY ALL OFF — RESET REQUIRED`.
- Use only a certified contactor + ISI-marked cable + correctly-rated fuse on the coil circuit.
- **Do NOT bridge this with a software relay** — it must remain purely physical.
- After an ALL-OFF, loads stay OFF until a human resets the switch (by design).

**Add this to the Section 11 checklist as mandatory:** `□ Physical master ALL-OFF tested: pressing it drops ALL automated loads even with hub unplugged.`

---

## 3. Gas Safety (LPG/Natural Gas)

### 3.1 Gas Properties
- **LPG (Propane/Butane):** Heavier than air → sinks to floor
- **Natural Gas (Methane):** Lighter than air → rises to ceiling
- **Explosive Range:** LPG 1.8%–8.4% in air

### 3.2 Sensor Placement
| Gas Type | Sensor Height | Location |
|----------|--------------|----------|
| LPG | 15-30cm from FLOOR | Near stove, low wall |
| Natural Gas | 30cm from CEILING | Near stove, high wall |

### 3.3 Gas Valve Requirements
- **Use certified brass/stainless steel solenoid valves only**
- **Normally Closed (NC)** — valve CLOSES when power lost (safe)
- **Pressure rating:** Must exceed your gas line pressure (typically 280 mbar)
- **Install shut-off valve BEFORE solenoid** for maintenance

### 3.4 Gas Leak Response Protocol
```
1. ESP32 detects gas → Exhaust fan ON, Gas valve CLOSE, Siren ON
2. Human hears siren →
   a. DO NOT switch on/off ANY electrical device
   b. Open all windows and doors
   c. Turn off gas cylinder valve (if LPG)
   d. Evacuate if smell is strong
   e. Call gas emergency number from OUTSIDE
3. After clearing:
   a. Ventilate for 30 minutes
   b. Check with soap solution on all joints
   c. Only then reset system
```

### 3.5 NEVER Do This
- ❌ Use plastic gas valves
- ❌ Install sensor at wrong height
- ❌ Ignore siren — always investigate
- ❌ Use electrical switches when gas smell detected
- ❌ Install gas valve without licensed plumber approval

---

## 4. Water Safety

### 4.1 Water Valve Requirements
- **Brass or stainless steel only** — no plastic on mains pressure
- **Normally Closed (NC)** — closes when power lost
- **Pressure rating:** Minimum 6 bar (most homes have 2-4 bar)
- **Install isolation valve before solenoid**

### 4.2 Leak Sensor Placement
- Under kitchen sink (drip loop area)
- Under bathroom sink
- Near washing machine
- Near water heater
- Near aquarium (if large)
- **Elevate electronics** — never on floor where water pools

### 4.3 Waterproofing
- **IP65 minimum** for any node near water
- **Cable glands** on all enclosures
- **Drip loops** on all cables entering enclosures
- **Silicone sealant** around sensor penetrations

### 4.4 Drip Loop
```
    Cable enters from above
         │
         ▼
    ┌────┴────┐  <-- Loop hangs DOWN before entering box
    │  ╭───╮  │      Water drips off loop, not into box
    │  │   │  │
    └────┬────┘
         │
    [Enclosure]
```

---

## 5. Fire Safety

### 5.1 Smoke Sensor Placement
- **One per floor minimum** (more in large homes)
- **Ceiling mount**, center of room or hallway
- **Away from:** Kitchen smoke, bathroom steam, air vents, ceiling fans
- **Distance from wall:** Minimum 10cm

### 5.2 Fire-Rated Enclosures
- **ABS V-0 rated** or **metal enclosures** for nodes near heat
- **Never use flammable materials** near electrical components
- **Keep enclosures away from:** Stove, geyser, heater

### 5.3 Emergency Cutoff
- **Main electrical cutoff** must be accessible without tools
- **Clearly labeled:** "EMERGENCY — MAIN POWER OFF"
- **Everyone in home must know location**

### 5.4 Fire Extinguisher
- **ABC type** (for electrical, liquid, solid fires)
- **Minimum 2kg** for home use
- **Place near kitchen and electrical panel**
- **Check pressure gauge monthly**

---

## 6. Chemical Safety (Sensors)

### 6.1 MQ Series Gas Sensors
- **Heating element reaches 300°C+** — do not touch when powered
- **Small amount of tin dioxide** — not hazardous in normal use
- **Do not disassemble** sensor element

### 6.2 Battery Safety (18650 / Li-ion)
- **Never puncture or crush**
- **Never short positive and negative terminals**
- **Charge only with proper charger** (TP4056 with protection)
- **Store in fire-safe container** when not in use
- **Dispose at e-waste center** — never in regular trash
- **If battery swells or gets hot:** Remove immediately, place in sand bucket

### 6.3 Soldering Safety
- **Work in ventilated area** — flux fumes are harmful
- **Use lead-free solder** when possible
- **Wear safety glasses** — solder can splatter
- **Iron temperature:** 300-350°C — hot enough to cause burns
- **Always place iron in stand** when not in use

---

## 7. Battery Safety (Li-ion)

### 7.1 Charging Safety
```
□ Use TP4056 module WITH protection (DW01A + FS8205A)
□ Never leave charging unattended overnight
□ Charge on non-flammable surface (metal tray, ceramic tile)
□ Do not charge damaged batteries
□ Stop charging if battery gets warm (>45°C)
```

### 7.2 Battery Fire Response
```
1. DO NOT use water on Li-ion fire
2. Use Class D fire extinguisher or sand
3. Evacuate area
4. Call fire department
5. Let it burn out in controlled manner if small
```

---

## 8. Installation Safety

### 8.1 Ladder Safety
- **3-point contact** at all times (two feet + one hand)
- **Never stand on top step**
- **Have someone hold ladder**
- **Check for overhead wires** before raising ladder

### 8.2 Working in Confined Spaces
- **Electrical panel:** Turn OFF main breaker, use flashlight
- **Attic/ceiling:** Watch for nails, insulation, heat
- **Under sink:** Check for leaks before working

### 8.3 Tool Safety
- **Insulated screwdrivers** for electrical work
- **Wire strippers** — never use teeth
- **Multimeter** — test before touching
- **Cable tester** — verify connections

---

## 9. Emergency Procedures

### 9.1 Electrical Shock
```
1. DO NOT touch victim if still in contact with electricity
2. Turn OFF power at main breaker FIRST
3. If cannot turn off power, use INSULATED object (wood, rubber) to separate victim
4. Call 108 (ambulance) immediately
5. If not breathing, start CPR if trained
6. Keep victim warm until help arrives
```

### 9.2 Gas Leak
```
1. DO NOT operate electrical switches
2. Open all doors and windows
3. Turn off gas at cylinder/main valve
4. Evacuate if strong smell
5. Call gas emergency from outside
6. Do not re-enter until cleared by professional
```

### 9.3 Fire
```
1. Raise alarm — shout "FIRE!"
2. Call 101 (fire department)
3. Evacuate everyone
4. Only attempt extinguishment if fire is SMALL and you have clear escape
5. Use PASS method: Pull, Aim, Squeeze, Sweep
6. If electrical fire: Turn OFF power first, use CO2 extinguisher
```

### 9.4 System Failure
```
1. If automation fails: All manual switches still work
2. If hub fails: Nodes continue local logic (ESPHome on-device)
3. If WiFi fails: Nodes with fallback AP can be accessed directly
4. Emergency cutoff: Physical switch always overrides automation
```

---

## 10. Compliance & Codes

### 10.1 Indian Electrical Standards
- **IS 3043:** Earthing
- **IS 732:** Electrical wiring
- **IS 14697:** Residual Current Devices (GFCI)
- **NEC 2023 (reference):** General electrical safety

### 10.2 Recommended Third-Party Inspection
Before energizing any mains-connected automation:
- **Licensed electrician** to verify wiring
- **Earth resistance test**
- **Insulation resistance test** (megger test)
- **GFCI functionality test**

### 10.3 Insurance Considerations
- Inform home insurance about automation system
- Keep documentation of certified components
- Photograph all installations before closing walls

---

## 11. Safety Checklist Before Power-On

### For EVERY Node:
```
□ All connections verified with multimeter
□ No loose wires or exposed conductors
□ Proper fuse installed
□ Earth connection verified
□ Enclosure properly closed
□ IP rating appropriate for location
□ Labels on all wires
□ Emergency cutoff accessible
□ No water near electrical components
□ Fire extinguisher within 10 meters
□ Someone else knows you're working
□ Phone charged and accessible
```

### For Safety-Critical Nodes (Gas, Fire, Water):
```
□ Double-checked all wiring
□ Tested with Wokwi simulation
□ Tested on breadboard before mains connection
□ Certified components only (valves, contactors, sensors)
□ Manual override switch installed and tested
□ Fail-safe position verified (power off = safe state)
□ Notification system tested
□ Family members trained on emergency procedures
□ Professional inspection completed (for mains work)
```

---

## Emergency Contact Card

Print and laminate this card. Keep one near main panel, one in kitchen:

```
╔══════════════════════════════════════╗
║     🚨 SMARTHOME EMERGENCY CARD      ║
╠══════════════════════════════════════╣
║ Main Power Cutoff: [Location]        ║
║ Gas Main Valve: [Location]           ║
║ Water Main Valve: [Location]         ║
║                                      ║
║ Electrician: [Name] [Phone]          ║
║ Plumber: [Name] [Phone]              ║
║ Gas Agency: [Name] [Phone]         ║
║                                      ║
║ Fire: 101                            ║
║ Ambulance: 102 / 108                 ║
║ Police: 100                          ║
║                                      ║
║ HA Remote: [Tailscale/CF URL]        ║
╚══════════════════════════════════════╝
```

---

> **"There is no project worth a hospital visit. When in doubt, hire a professional."**

---

*End of 09_Safety_Guidelines.md*
*Next: 10_Procurement_India_Links.md*
