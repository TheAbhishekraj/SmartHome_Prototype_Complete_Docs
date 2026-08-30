# 📸 SmartHome & Commercial IoT — Visual Schematics & Wiring Gallery

> **Interactive Vector Wiring Schematics, Architecture Blueprints, and Physical Build Diagrams.**  
> *All diagrams are publication-grade SVGs rendered directly from the validated Wokwi simulation and hardware pinouts.*

---

## 🌐 Whole-House Distributed System Architecture

![Whole House System Architecture](https://raw.githubusercontent.com/TheAbhishekraj/SmartHome_Prototype_Complete_Docs/master/photos/wiring/whole_home_system_architecture.svg)

---

## 🖼️ Complete Project Visual Schematics Gallery

### 1. Smart Room Light & Fan Retrofit (Modular Switchboard)
*Node ID:* `NODE-D1 / D2 / D3 / D4` | *Simulation:* `simulations/08_smart_room_light_fan_auto_switch`  
*Features:* Detached 2-Way Wall Switch Sync, PIR Occupancy Auto-Off, LDR Twilight Lux Gating, DHT22 Climate Fan, and RC Snubber Protection.

![Smart Room Switchboard Retrofit](https://raw.githubusercontent.com/TheAbhishekraj/SmartHome_Prototype_Complete_Docs/master/photos/wiring/08_smart_room_fan_light_switchboard.svg)

---

### 2. Commercial Retail Shop & Heavy Appliance Automation
*Node ID:* `SHOP-01 to 05` | *Guide:* `20_Commercial_Shop_and_Appliance_Automation_Guide.md`  
*Features:* 25A Modular Contactor for Facade Glow-Signs, Deep-Freezer Cold-Chain Monitoring (-18°C), Armored Roller Shutter Intrusion Alarm, and Store AC Interlock.

![Commercial Shop Automation](https://raw.githubusercontent.com/TheAbhishekraj/SmartHome_Prototype_Complete_Docs/master/photos/wiring/12_commercial_shop_automation.svg)

---

### 3. Mains Power Monitor & Peak Demand Load Shedder
*Node ID:* `NODE-E1` | *Simulation:* `simulations/09_energy_monitor_load_shedding`  
*Features:* Real-time current & wattage metering (0–25A), 16x2 I2C LCD telemetry, and automated shedding of heavy appliances during peak load.

![Energy Monitor Load Shedding](https://raw.githubusercontent.com/TheAbhishekraj/SmartHome_Prototype_Complete_Docs/master/photos/wiring/09_energy_monitor_load_shedding.svg)

---

### 4. Kitchen LPG Gas Leak & Safety Interlock
*Node ID:* `NODE-B1` | *Simulation:* `simulations/04_gas_leak`  
*Features:* MQ-6 LPG gas sensing, automatic exhaust ventilation purge, emergency fail-safe gas solenoid cutoff, and 110dB siren alarm.

![Kitchen Gas Safety](https://raw.githubusercontent.com/TheAbhishekraj/SmartHome_Prototype_Complete_Docs/master/photos/wiring/04_kitchen_gas_safety.svg)

---

### 5. Ultrasonic Overhead Water Tank & Dry-Run Protection
*Node ID:* `NODE-C1` | *Simulation:* `simulations/05_water_tank`  
*Features:* HC-SR04 ultrasonic water depth sensing, automated pump contactor switching (Auto ON <20%, OFF >95%), and sump dry-run float cutoff.

![Water Tank Ultrasonic](https://raw.githubusercontent.com/TheAbhishekraj/SmartHome_Prototype_Complete_Docs/master/photos/wiring/05_water_tank_ultrasonic.svg)

---

### 6. Indoor Air Quality & Automated Exhaust Fan
*Node ID:* `NODE-B1` | *Simulation:* `simulations/10_air_quality_auto_exhaust`  
*Features:* MQ-135 CO2/VOC/Smoke sensing, 3-stage status LEDs (Green/Yellow/Red), and automatic exhaust fan purge cycle with anti-chatter hysteresis.

![Air Quality Auto Exhaust](https://raw.githubusercontent.com/TheAbhishekraj/SmartHome_Prototype_Complete_Docs/master/photos/wiring/10_air_quality_auto_exhaust.svg)

---

### 7. Smart Doorbell, Bedside Panic Button & Fall Alarm
*Node ID:* `NODE-F1 / F4 / F5` | *Simulation:* `simulations/11_smart_doorbell_panic_fall`  
*Features:* 2-tone melodic visitor chime, latching emergency distress panic button, elder fall impact sensor, and master disarm reset switch.

![Smart Doorbell Panic Fall](https://raw.githubusercontent.com/TheAbhishekraj/SmartHome_Prototype_Complete_Docs/master/photos/wiring/11_smart_doorbell_panic_fall.svg)

---

### 8. PIR Motion Activated Lighting
*Node ID:* `NODE-B2` | *Simulation:* `simulations/01_pir_motion_light`  
*Features:* AM312/HC-SR501 PIR motion trigger, 30s auto-off vacancy countdown, and yellow indicator relay.

![PIR Motion Light](https://raw.githubusercontent.com/TheAbhishekraj/SmartHome_Prototype_Complete_Docs/master/photos/wiring/01_pir_motion_light.svg)

---

### 9. DHT22 Ambient Climate & Comfort Fan
*Node ID:* `NODE-D1` | *Simulation:* `simulations/02_dht22_climate`  
*Features:* DHT22 digital temperature & humidity sensing with 1.5°C hysteresis band to prevent relay fluttering.

![DHT22 Climate Fan](https://raw.githubusercontent.com/TheAbhishekraj/SmartHome_Prototype_Complete_Docs/master/photos/wiring/02_dht22_climate_fan.svg)

---

### 10. Automated Garden Soil Moisture & Pump
*Node ID:* `NODE-A1` | *Simulation:* `simulations/03_soil_moisture_pump`  
*Features:* Capacitive soil moisture sensing, automated water solenoid pump, and 20s anti-flood timeout safety.

![Soil Moisture Pump](https://raw.githubusercontent.com/TheAbhishekraj/SmartHome_Prototype_Complete_Docs/master/photos/wiring/03_soil_moisture_pump.svg)

---

### 11. Magnetic Reed Switch Perimeter Security
*Node ID:* `NODE-F3` | *Simulation:* `simulations/06_reed_door`  
*Features:* Debounced internal pull-up input, door/window state detection, and perimeter alarm dispatch.

![Reed Door Security](https://raw.githubusercontent.com/TheAbhishekraj/SmartHome_Prototype_Complete_Docs/master/photos/wiring/06_reed_door_security.svg)

---

### 12. Motorized Stepper Curtains (Authoritative D1 Pinout)
*Node ID:* `NODE-D1` | *Simulation:* `simulations/07_stepper_curtain`  
*Features:* A4988 stepper driver controlling NEMA-17 / 28BYJ-48 stepper motors with collision-free GPIO pin mapping.

![Stepper Curtain](https://raw.githubusercontent.com/TheAbhishekraj/SmartHome_Prototype_Complete_Docs/master/photos/wiring/07_stepper_curtain.svg)

---

## 🛠️ Step-by-Step Making Manual & Hardware Assembly
For detailed soldering instructions, wire gauge sizing (0.5mm² vs 2.5mm²), perfboard creepage isolation slots, and pre-commissioning testing, consult:  
👉 [`19_Hardware_Fabrication_and_Making_Manual.md`](https://github.com/TheAbhishekraj/SmartHome_Prototype_Complete_Docs/blob/master/19_Hardware_Fabrication_and_Making_Manual.md)

---

## ⚡ Industry Standards & AC Safety Compliance
For Bureau of Indian Standards (IS 732, IS 13947) and International (IEC 60669-2-1, IEC 60947) electrical safety codes, see:  
👉 [`21_Industry_Standards_IS_IEC_Compliance_and_AC_Safety.md`](https://github.com/TheAbhishekraj/SmartHome_Prototype_Complete_Docs/blob/master/21_Industry_Standards_IS_IEC_Compliance_and_AC_Safety.md)