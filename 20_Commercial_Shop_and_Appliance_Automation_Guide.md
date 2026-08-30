# 20_Commercial_Shop_and_Appliance_Automation_Guide.md
# 🏢 Commercial, Retail Shop & Heavy Appliance Automation Blueprint

**Application Domains:** Retail Stores, Pharmacies, Restaurants, Supermarkets, Small Offices, Heavy Residential Appliances (1.5–2 Ton ACs, Geysers, Submersible Pumps)  
**Electrical Compatibility:** Single-Phase 230V AC & Three-Phase 415V AC (R-Y-B-N Distribution)

---

## 1. Overview & Business Value

While originally prototyped for residential flats, this IoT architecture extends directly to commercial shops and high-power appliances. Commercial deployments solve critical operational pain points:
- **Electricity Waste:** Automatic shutdown of air conditioners, shop lighting, and display racks after closing hours.
- **Perishable Inventory Protection:** 24/7 temperature monitoring of commercial deep freezers, milk coolers, and pharmacy vaccine refrigerators with instant SMS/Telegram/MQTT power-loss alerts.
- **Facade Signboard Automation:** Astronomical twilight / sunset-to-midnight timer control for outdoor LED glow-sign boards.
- **Perimeter & Shutter Security:** Magnetic roller shutter contact sensors + loud intrusion sirens with cellular/WiFi redundancy.

---

## 🖼️ Commercial Shop & Retail Automation Schematic

![Commercial Shop Automation Schematic](https://raw.githubusercontent.com/TheAbhishekraj/SmartHome_Prototype_Complete_Docs/master/photos/wiring/12_commercial_shop_automation.svg)

---

## 2. Commercial Shop Automation Matrix

| Node ID | Sub-System | Hardware Involved | Target Commercial Function |
|---|---|---|---|
| **SHOP-01** | **Glow-Signboard & Facade** | ESP32 + 25A Contactor + LDR | Turns facade glow-sign ON at dusk, OFF at 11:00 PM; turns back ON 5:00 AM–6:30 AM. Saves ₹1,200/month. |
| **SHOP-02** | **Cold-Chain & Freezer Monitor** | ESP32 + DS18B20 (Waterproof) + ACS712 | Monitors deep freezer (-18°C) and milk cooler (4°C). Alerts immediately if temperature rises > threshold or mains fails. |
| **SHOP-03** | **Roller Shutter Security Alarm** | ESP32 + Heavy-Duty Iron Shutter Reed + 110dB Siren | Detects unauthorized shutter lift after shop closing; triggers local siren and dispatches phone push alerts. |
| **SHOP-04** | **Central AC & Inverter Interlock** | ESP32 + 32A 230V Modular Contactor | Automatically disconnects high-draw commercial air conditioners when operating on backup inverter/generator. |
| **SHOP-05** | **Customer Footfall Counter** | ESP32 + VL53L0X ToF Laser / IR Beam | Counts incoming/outgoing customers through the entrance door for retail footfall conversion analytics. |

---

## 3. Detailed Circuit & Wiring Specifications for Commercial Applications

### 3.1 Facade Glow-Signboard & Heavy Lighting Controller
Standard LED glow-sign boards draw high inrush capacitive current (SMPS drivers) that weld standard 10A micro-relays.

**Commercial Wiring Rule:**
```
                     +---------------------------------------+
230V Phase (L) ──────┤ Modular 25A AC Contactor (Terminal 1) ├───> Outdoor Glow-Sign
                     │                                       │
230V Neutral (N) ────┤ Modular 25A AC Contactor (Terminal 3) ├───> Outdoor Glow-Sign
                     │                                       │
ESP32 Relay (COM/NO) ┼── Energizes 230V Contactor Coil (A1/A2)
                     +---------------------------------------+
```
- The ESP32 low-power relay switches **only the contactor coil** (\(<5\text{W}\)).
- The heavy 25A contactor poles switch the 1000W+ outdoor lighting load safely without arcing.

---

### 3.2 Deep Freezer & Pharmacy Cold-Chain Monitor
Ensures ice cream, dairy, meats, and temperature-sensitive medicines never spoil during overnight power cuts.

- **Sensors:**
  - DS18B20 Stainless-Steel Waterproof Temperature Probe placed inside the refrigeration cavity.
  - Optocoupler AC Mains Voltage Presence Detector (PC817 based) on `GPIO35` to detect utility power loss instantly.
  - Backup 18650 Li-ion battery shield with TP4056 + Boost converter to keep the ESP32 transmitting during a blackout.
- **Thresholds & Alerts:**
  - Freezer Critical Alert: Temperature \(> -12^\circ\text{C}\) for \(> 15\text{ minutes}\).
  - Pharmacy Vaccine Fridge Alert: Temperature \(> 8.0^\circ\text{C}\) or \(< 2.0^\circ\text{C}\).
  - Notification Channels: Home Assistant Push Notifications, Telegram Bot API, and Twilio Emergency SMS call.

---

### 3.3 Heavy-Duty Roller Shutter Intrusion Alarm
Commercial rolling shutters require armored magnetic contacts that withstand vibration and dust.

- **Sensor:** Industrial Grade Armored Surface Mount Shutter Contact (Zinc alloy housing, flexible stainless-steel conduit cable).
- **Wiring:** Connected between ESP32 `GPIO14` and `GND` with internal pull-up.
- **Arming Schedule:**
  - Auto-armed at 10:30 PM (or when owner clicks "Close Shop" on dashboard).
  - If shutter contact breaks while armed:
    1. Instantly drives `GPIO23` HIGH to fire an outdoor 12V 110dB Piezo Siren.
    2. Blinks all store interior lights rapidly.
    3. Dispatches high-priority alert with timestamp and snapshot from the shop CCTV camera.

---

## 4. Heavy Residential Appliance Wiring (Geysers, ACs & Pumps)

### Sizing Guide for High-Power Residential Appliances

```
+------------------------------------------------------------------------------------+
| Appliance           | Power Rating | Running Current | Contactor / Relay Rating    |
|---------------------|--------------|-----------------|-----------------------------|
| 1.5 Ton Inverter AC | 1,500 - 1,800W| 6.5 - 8.0 A    | 20A Contactor (AC-7a rated) |
| 2.0 Ton Inverter AC | 2,200 - 2,600W| 9.5 - 11.5 A   | 25A Contactor (AC-7a rated) |
| 25L Water Geyser    | 2,000 - 3,000W| 8.7 - 13.0 A   | 25A Contactor (AC-7a rated) |
| 1.0 HP Submersible  | 750 - 1,100W  | 5.0 - 7.5 A     | 16A Contactor + Snubber     |
| 2.0 HP Water Pump   | 1,500 - 2,200W| 10.0 - 14.5 A   | 25A Motor-Rated Contactor   |
+------------------------------------------------------------------------------------+
```

> [!IMPORTANT]
> **Motor & Inductive Loads (AC-7b / AC-3 Rating):**
> Pumps and AC compressors have locked-rotor inrush currents 4 to 6 times their running current. Always specify contactors rated for inductive motor duty (**AC-3 / AC-7b standard**) rather than generic resistive (AC-1) ratings.

---

## 5. Commercial Dashboard & Multi-Store Management

When deploying across multiple retail outlets or shops:
1. **Centralized Home Assistant Core:** Run on a central cloud VM (AWS / Hetzner / Linode) or on-premise hub connected via encrypted **Tailscale VPN mesh**.
2. **Per-Store Tabular Overview:**
   - Real-time temperature of all freezers across all branches.
   - Live power consumption & current billing tier.
   - Shutter status (Open / Closed / Armed) with opening/closing timestamps.
   - Energy savings metrics (kWh saved by auto-shutoff).
