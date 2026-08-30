# 21_Industry_Standards_IS_IEC_Compliance_and_AC_Safety.md
# ⚡ Industry Standards, Electrical Codes (IS / IEC) & 230V AC Safety Compliance

**Governing Standards:** Bureau of Indian Standards (BIS), International Electrotechnical Commission (IEC), Central Electricity Authority (CEA) Regulations  
**Applicability:** 230V AC Single-Phase 50Hz, 415V AC Three-Phase 50Hz Domestic & Commercial Fixed Electrical Installations

---

## 1. Regulatory Framework & Standards Cross-Reference

To ensure commercial viability, legal compliance, and human life safety, all physical nodes and switchboard retrofits must conform to the following standards:

| Standard Code | Standard Title | Application in SmartHome Prototype |
|---|---|---|
| **IS 732 (2019)** | Code of Practice for Electrical Wiring Installations | Cable sizing, color coding, earthing conductor continuity & switchboard conduit wiring |
| **IS 13947 / IEC 60947** | Low-Voltage Switchgear and Controlgear | Specification and de-rating of electromagnetic contactors, relays & circuit breakers |
| **IEC 60669-2-1** | Switches for Household and Similar Fixed Electrical Installations — Electronic Switches | Microcontroller-controlled electronic switches, standby power consumption & EMC immunity |
| **IS 12640 / IEC 61008** | Residual Current Operated Circuit-Breakers (RCCB / ELCB) | Mandatory 30mA residual current protection on all lighting and power sub-circuits |
| **UL 94** | Tests for Flammability of Plastic Materials for Parts in Devices and Appliances | V-0 fire-retardant rating requirement for all 3D printed / molded enclosure plastics |
| **RoHS (2011/65/EU)** | Restriction of Hazardous Substances | Lead-free solder and component compliance for commercial PCB production |

---

## 2. 230V AC PCB Layout & Safety Isolation Rules

When designing custom PCBs or perfboard assemblies for in-switchboard installation, strict isolation boundaries must be maintained between the High-Voltage (230V AC) domain and the Low-Voltage (3.3V / 5V DC) domain.

```
+-------------------------------------------------------------------------------+
|                       HIGH-VOLTAGE PCB ISOLATION RULES                        |
+-------------------------------------------------------------------------------+
| Parameter                        | Minimum Required Value | Our Design Value  |
|----------------------------------|------------------------|-------------------|
| Creepage Distance (AC to DC)     | 5.0 mm                 | >= 6.3 mm         |
| Clearance Distance (Air Gap)     | 3.0 mm                 | >= 4.5 mm         |
| Isolation Barrier Slot Width     | 1.5 mm                 | 2.0 mm routed slot|
| High-Voltage Trace Width (10A)   | 2.5 mm (2 oz copper)   | 3.0 mm + Tinned   |
| High-Voltage Trace Width (16A)   | 4.0 mm (2 oz copper)   | 5.0 mm + Copper   |
| Dielectric Withstand Voltage     | 2,000V AC (1 minute)   | 2,500V Opto-isol  |
+-------------------------------------------------------------------------------+
```

```
       MAINS 230V AC DOMAIN                     LOW-VOLTAGE DC DOMAIN (ESP32)
   ┌───────────────────────────┐             ┌────────────────────────────────┐
   │ AC Phase (L) ──── Fuse ─┐ │             │                                │
   │                         ▼ │             │  +3.3V / +5V DC Supply Rail    │
   │ AC Neutral (N) ── MOV ──┤ │  PHYSICAL   │                                │
   │                         │ │ ROUTED SLOT │  ESP32-WROOM-32D Core          │
   │ Relay Contacts (NO/COM) ├─┼─────────────┼─ Optocoupler (PC817 / EL817)   │
   │                         │ │  (>= 2.0mm) │                                │
   │ RC Snubber (400V Film)  │ │             │  GPIO Sensing & Control Logic  │
   └───────────────────────────┘             └────────────────────────────────┘
```

---

## 3. Four Essential Protection Stages

Every mains-connected node must incorporate the following four protection elements:

### Stage 1: Over-Current Protection (Fusible Link)
- **Fast-Blow Ceramic Cartridge Fuse (5x20mm)** or **PolySwitch Resettable PTC**:
  - Rated at `1.0A / 250V` for sensor/control electronics.
  - Rated at `6.0A / 250V` for lighting circuits.
  - Rated at `16.0A` for heavy appliance circuits.

### Stage 2: Transient Over-Voltage Surge Protection (MOV)
- **Metal Oxide Varistor (MOV):** `14D471K` (470V clamping voltage, 4.5kA surge capacity).
- Connected directly across Phase and Neutral before the SMPS power supply.
- Absorbs lightning-induced spikes and utility switching transients common in Indian power grids.

### Stage 3: Thermal Runaway Protection (Thermal Cutoff)
- **One-Shot Thermal Fuse (102°C / 250V 2A)** placed in physical contact with the Hi-Link SMPS module.
- In the event of a component failure causing internal heating, the thermal fuse permanently opens, preventing fire.

### Stage 4: Inductive Kickback Snubber (RC Network)
- **X2 Rated Metallized Polypropylene Safety Film Capacitor (0.1µF / 275V–400V AC)** in series with a **100Ω 2W Flameproof Metal Oxide Resistor**.
- Quenches electric arcs when switching ceiling fans, exhaust fans, and pump motor contactors.

---

## 4. Grounding & Earth Leakage (RCCB) Integration

1. **Mandatory 30mA RCCB Protection:**
   - Under Central Electricity Authority (CEA) safety guidelines, all domestic and commercial sub-circuits feeding smart nodes must be protected upstream by an ISI-marked **30mA Residual Current Circuit Breaker (RCCB / ELCB)**.
   - The low-voltage DC ground (`GND`) of the ESP32 must remain **galvanically isolated** from Mains Earth and Neutral.
2. **Earth Continuity Testing:**
   - Verify that the Earth resistance to the central copper earth electrode is **less than 5.0 Ohms** using a calibrated Earth Megger / Loop Impedance Tester.

---

## 5. Certification & Compliance Checklist for Commercialization

| Compliance Gate | Testing Standard | Pass / Fail Criteria | Verification Method |
|---|---|---|---|
| **Dielectric Strength (Hi-Pot)** | IEC 60950-1 | 2.5 kV AC applied for 60s between AC input and low-voltage output | Leakage current < 0.5 mA |
| **Insulation Resistance** | IS 732 §8.3 | 500V DC applied between live conductors and earth | Resistance > 50 MΩ |
| **Temperature Rise** | IEC 60669-2-1 | Full load operation at 40°C ambient for 8 hours | Max enclosure temp < 65°C |
| **Flammability Test** | UL 94 | Glow wire flammability index (GWFI) on plastic casing | Self-extinguishes < 30s at 850°C |
| **EMC Conducted Emissions** | CISPR 32 / EN 55032 | RF emissions injected back into mains wiring | Within Class B domestic limits |
| **ESD Immunity** | IEC 61000-4-2 | Contact discharge ±4kV, Air discharge ±8kV on exposed touch surfaces | No microcontroller resets or lockups |
