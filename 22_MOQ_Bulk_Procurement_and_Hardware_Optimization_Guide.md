# 22_MOQ_Bulk_Procurement_and_Hardware_Optimization_Guide.md
# 🛒 Hardware Procurement, MOQ Optimization & Batch Buying Guide

**Version:** 1.0 | **Target:** Minimizing Microcontroller Count via Node Clubbing & Maximizing Margin via Bulk MOQ Packs  
**Companion File:** [`PROCUREMENT_AND_MOQ_README.md`](file:///PROCUREMENT_AND_MOQ_README.md)

---

## 1. Executive Summary & Strategy

This document establishes the procurement and hardware scaling strategy for the whole-home automation system. By implementing **zone clubbing** (1 multi-functional ESP32 per room) and purchasing components in standard wholesale **Minimum Order Quantities (MOQs)**, the total prototype cost is reduced to **₹37,500** for a full 2-floor flat, scaling down to **₹16,800 per home** at commercial production scale.

---

## 2. Zone Clubbing Architecture: Reducing 40 Nodes to 15

Rather than deploying individual smart plugs or single-channel relays, each room uses a single ESP32 node configured to handle:
- Up to 4 load relays (lighting, ceiling fan, exhaust fan)
- Up to 4 physical dry-contact wall switch inputs (GPIOs with pullups)
- Shared 2-pin I2C bus (`GPIO21`/`GPIO22`) for environmental sensors (OLED display, BH1750 lux meter, BME280 climate sensor)
- Dedicated analog sensors on input-only pins (`GPIO34`, `GPIO35`, `GPIO36`, `GPIO39`)

---

## 3. Minimum Order Quantity (MOQ) Wholesale Pack Matrix

| Component Name | Standard MOQ Pack Size | Retail Single Unit Cost | Bulk MOQ Unit Cost | Verified Supplier | Savings |
|---|:---:|:---:|:---:|---|:---:|
| **ESP32-WROOM-32D (38-Pin DevBoard)** | **10-Pack** | ₹450 | **₹310** | Robu.in / Evelta | **31%** |
| **Hi-Link HLK-PM01 (5V 1A Isolated SMPS)** | **10-Pack** | ₹240 | **₹155** | Evelta / ElectronicsComp | **35%** |
| **2-Channel 5V Optocoupler Relay Board** | **10-Pack** | ₹140 | **₹85** | Robu.in / Amazon Business | **39%** |
| **4-Channel 5V Optocoupler Relay Board** | **5-Pack** | ₹260 | **₹165** | Robu.in / ElectronicsComp | **36%** |
| **AM312 Mini PIR Motion Sensors** | **10-Pack** | ₹90 | **₹48** | Robu.in / ElectronicsComp | **46%** |
| **DHT22 / AHT20 Climate Sensors** | **5-Pack** | ₹280 | **₹185** | Robu.in / Evelta | **34%** |
| **RC Snubber Modules (400V 0.1uF + 100R)** | **20-Pack** | ₹60 | **₹24** | Robu.in / LCSC | **60%** |
| **MOV 14D471K Transient Surge Arrestors** | **50-Pack Box** | ₹15 | **₹4** | Evelta / ElectronicsComp | **73%** |
| **WAGO 221-413 Lever Wire Connectors** | **50-Pack Box** | ₹35 | **₹18** | Amazon Business | **48%** |
| **5.08mm Pitch Screw Terminal Blocks** | **50-Pack** | ₹12 | **₹4.5** | ElectronicsComp / Evelta | **62%** |
| **FR4 Double-Sided Perfboards (5x7cm)** | **10-Pack** | ₹60 | **₹22** | Robu.in / Amazon | **63%** |
| **Modular 25A DIN AC Contactors** | **5-Pack** | ₹650 | **₹420** | Schneider / Havells / Indiamart | **35%** |

---

## 4. Bulk Procurement Tiers & Scaling Economics

```
+-------------------------------------------------------------------------------+
|                      SYSTEM COST SCALING ACROSS TIERS                         |
+-------------------------------------------------------------------------------+
| Tier                    | Description                  | Unit Cost per Flat   |
|-------------------------|------------------------------|----------------------|
| Tier 1: Prototype Kit   | 1 Flat (15 Custom Nodes)     | ₹37,500 (~$450 USD)  |
| Tier 2: Builder Batch   | 3 Flats / 5 Shops Batch      | ₹24,200 (~$290 USD)  |
| Tier 3: Commercial PCB  | 10+ Flats (Factory SMT Sized)| ₹16,800 (~$200 USD)  |
+-------------------------------------------------------------------------------+
```

---

## 5. Direct Procurement Links & Supplier Contacts
- **Robu.in:** [https://robu.in](https://robu.in)
- **Evelta Electronics:** [https://www.evelta.com](https://www.evelta.com)
- **ElectronicsComp:** [https://www.electronicscomp.com](https://www.electronicscomp.com)
- **Amazon Business India:** [https://business.amazon.in](https://business.amazon.in)
- **JLCPCB / LCSC Electronics:** [https://jlcpcb.com](https://jlcpcb.com)
