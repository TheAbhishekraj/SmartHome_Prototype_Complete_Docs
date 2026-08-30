# 🛒 Hardware Procurement, MOQ Optimization & Batch Buying Guide

> **CTO Blueprint: How to build maximum whole-home automation projects with the MINIMUM number of microcontrollers, multiplexed sensors, and wholesale Minimum Order Quantity (MOQ) batch discounts.**

---

## 1. The Core Optimization Principle: "Zone Clubbing & Sensor Multiplexing"

Commercial off-the-shelf smart home setups (Sonoff, Tuya, Shelly) sell single-purpose smart plugs or single-switch modules. Automating a 2-floor, 2000 sq ft flat using single-switch devices requires **40+ microcontrollers**, resulting in:
- High hardware cost (>₹80,000)
- 40+ separate power supplies clogging switchboards
- Severe 2.4 GHz WiFi router congestion and dropped packets

### Our Engineering Optimization:
We use **1 multi-functional ESP32 microcontroller per zone / room**. A single ESP32 ($340) runs 4 to 8 tasks simultaneously over hardware interrupts and the shared I2C bus:

```
                  +----------------------------------------------+
                  |         ONE SINGLE ESP32-WROOM NODE          |
                  +----------------------------------------------+
                                         │
        ┌───────────────────┬────────────┴───────┬───────────────────┐
        ▼                   ▼                    ▼                   ▼
  [4x Load Relays]   [4x Wall Switches]   [Shared I2C Bus]   [Safety Sensors]
  • Ceiling Light 1   • Wall Rocker 1      • I2C Lux Sensor   • PIR Occupancy
  • Ceiling Light 2   • Wall Rocker 2      • I2C Temp & Hum   • Gas Sensor / Flame
  • Ceiling Fan       • Wall Rocker 3      • I2C OLED Display • Reed Contact
  • Exhaust Fan       • Wall Rocker 4      (All on 2 GPIOs!)  • RC Snubbers
```

**Result:** The entire 2-floor, 2000 sq ft home (8 zones, 40+ automations) is powered by just **12 to 15 ESP32 nodes** instead of 40+ individual devices.

---

## 2. Recommended Minimum Order Quantity (MOQ) & Wholesale Pack Matrix

By purchasing components in standardized wholesale pack sizes (MOQs) from authorized Indian distributors (Robu.in, Evelta, ElectronicsComp, Amazon Business) or international fabs (JLCPCB/LCSC), you save **35% to 55%** compared to buying individual retail units.

| Component Name | Best Wholesale MOQ Pack | Retail Single Price | Wholesale Unit Price in MOQ | Recommended Vendor / Platform | Savings % |
|---|:---:|:---:|:---:|---|:---:|
| **ESP32-WROOM-32D (38-Pin)** | **10-Pack** | ₹450 / pc | **₹310 / pc** | Robu.in / Evelta / Amazon Biz | **31%** |
| **Hi-Link HLK-PM01 (5V 1A SMPS)** | **10-Pack** | ₹240 / pc | **₹155 / pc** | Evelta / ElectronicsComp | **35%** |
| **2-Channel 5V Optocoupler Relay** | **10-Pack** | ₹140 / pc | **₹85 / pc** | Robu.in / Amazon Business | **39%** |
| **4-Channel 5V Optocoupler Relay** | **5-Pack** | ₹260 / pc | **₹165 / pc** | Robu.in / ElectronicsComp | **36%** |
| **AM312 Discreet Mini PIR Sensors** | **10-Pack** | ₹90 / pc | **₹48 / pc** | Robu.in / ElectronicsComp | **46%** |
| **DHT22 / AHT20 Climate Sensors** | **5-Pack** | ₹280 / pc | **₹185 / pc** | Robu.in / Evelta | **34%** |
| **RC Snubber Modules (400V 0.1uF)** | **20-Pack** | ₹60 / pc | **₹24 / pc** | Robu.in / LCSC / Local Market | **60%** |
| **MOV 14D471K Surge Arrestors** | **50-Pack Box** | ₹15 / pc | **₹4 / pc** | Evelta / ElectronicsComp | **73%** |
| **WAGO 221-413 Lever Connectors** | **50-Pack Box** | ₹35 / pc | **₹18 / pc** | Amazon / Electrical Distributor | **48%** |
| **5.08mm Screw Terminal Blocks** | **50-Pack** | ₹12 / pc | **₹4.5 / pc** | ElectronicsComp / Evelta | **62%** |
| **FR4 Double-Sided Perfboards (5x7cm)**| **10-Pack** | ₹60 / pc | **₹22 / pc** | Robu.in / Amazon Business | **63%** |
| **Modular 25A AC Contactors (DIN)** | **5-Pack** | ₹650 / pc | **₹420 / pc** | Schneider / Havells / Indiamart | **35%** |

---

## 3. Standard MOQ Procurement Bundles

### 📦 Bundle A: "Single Flat Master Prototype Pack" (Builds 1 Complete 2-Floor Flat)
*Target:* All 15 Nodes (Garden, Kitchen Safety, Water Tank, 4 Bedrooms, Living Room, Power Monitor, Doorbell & Panic).

- **15x** ESP32-WROOM-32D DevBoards
- **15x** Hi-Link 5V 1A Isolated Power Modules
- **8x** 2-Channel Relay Boards + **4x** 4-Channel Relay Boards
- **10x** AM312 Mini PIR Sensors + **6x** LDRs
- **6x** DHT22 / AHT20 Climate Sensors
- **1x** MQ-6 Gas Sensor + **1x** MQ-135 Air Quality Sensor
- **1x** HC-SR04 Waterproof Ultrasonic Sensor + **1x** Float Switch
- **1x** PZEM-004T AC Power Meter + Split CT Clamp
- **20x** RC Snubber Modules + **30x** MOV 14D471K
- **1x** Hardware Accessories Kit (WAGO connectors, perfboards, heat-shrink, headers)
- **Total Prototype Hardware Cost:** **₹28,500** (Hardware BOM) + ₹9,000 (Certified Safety Solenoid, Master Contactor, UPS Battery) = **₹37,500 Total**

---

### 📦 Bundle B: "3-Home Builder / Commercial Shop Pilot Pack" (MOQ Scale Tier)
*Target:* Automating 3 complete residential flats or 5 commercial retail shops.

- **50x** ESP32 DevBoards (Wholesale tray)
- **50x** Hi-Link 5V SMPS modules
- **40x** Relay Modules + **50x** AM312 PIR sensors
- **100x** RC Snubbers & MOV Surge Protectors
- **Bulk Cost per Home:** Drops from ₹37,500 down to **₹24,200 per home** (35% Net Margin Improvement).

---

### 📦 Bundle C: "10-Home Commercial PCB Scaled Production" (Factory SMT Tier)
*Target:* Custom 2-layer PCBs fabricated and surface-mount assembled via JLCPCB / PCBWay.

- Replaces loose perfboards with custom **Smart Switchboard Retrofit PCBs**.
- Direct factory component procurement via LCSC electronics.
- **Factory Cost per Home:** Drops to **₹16,800 per home** (Over 55% Cost Reduction).
- **Target Commercial Sale Price:** ₹45,000–₹65,000 per home (65%+ Gross Profit Margin).

---

## 4. How to Maximize GPIO Efficiency on a Single ESP32

To avoid needing extra microcontrollers, use these 3 hardware design techniques:

### Technique 1: Shared I2C Sensor Bus (2 Pins for 8+ Devices)
Connect `GPIO21 (SDA)` and `GPIO22 (SCL)` to multiple I2C devices simultaneously with unique hex addresses:
- `0x27` or `0x3F`: 16x2 / 20x4 LCD Display
- `0x3C`: 0.96" OLED Display
- `0x23`: BH1750 High-Precision Lux Sensor
- `0x76` or `0x77`: BME280 / BMP280 Temperature, Humidity & Pressure Sensor
- `0x48`: ADS1115 16-Bit 4-Channel Analog-to-Digital Converter

### Technique 2: Input-Only ADC Pins (GPIO 34, 35, 36, 39)
The ESP32 has 4 dedicated analog input pins (`GPIO34`, `GPIO35`, `GPIO36/VP`, `GPIO39/VN`). Dedicate these exclusively to analog sensors (MQ Gas sensors, CT Current Clamps, Soil Moisture, LDRs) so all bidirectional digital GPIOs remain free for relays and wall switches.

### Technique 3: Detached Dry-Contact Wall Switches
Connect existing mechanical wall switches directly between GPIOs (configured with internal `INPUT_PULLUP`) and GND. No external resistors or high-voltage lines required.

---

## 5. Verified Direct Procurement Vendor Links (India & Global)

| Vendor | Region | Specialties & Best For | Direct Website |
|---|---|---|---|
| **Robu.in** | India | ESP32s, sensors, relay boards, Wokwi-compatible parts | [https://robu.in](https://robu.in) |
| **Evelta Electronics** | India | Hi-Link power supplies, MOVs, fuses, passives | [https://www.evelta.com](https://www.evelta.com) |
| **ElectronicsComp** | India | Terminal blocks, perfboards, PIRs, budget bundles | [https://www.electronicscomp.com](https://www.electronicscomp.com) |
| **Amazon India Business** | India | WAGO connectors, DIN contactors, wire spools | [https://business.amazon.in](https://business.amazon.in) |
| **JLCPCB / LCSC** | Global | Custom PCB manufacturing & SMT assembly | [https://jlcpcb.com](https://jlcpcb.com) |

---

*For step-by-step soldering and fabrication instructions, refer to [19_Hardware_Fabrication_and_Making_Manual.md](https://github.com/TheAbhishekraj/SmartHome_Prototype_Complete_Docs/blob/master/19_Hardware_Fabrication_and_Making_Manual.md).*
