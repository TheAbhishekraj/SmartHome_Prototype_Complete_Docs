# 🏠 SmartHome Prototype — Whole-Home Automation for 2-Floor Flat

> **From scrap to smart — a complete, local, privacy-first home automation system built with ESP32 microcontrollers, Home Assistant, Wokwi simulations, and Indian market modular switchboard retrofits.**

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Status](https://img.shields.io/badge/status-production--ready-green.svg)
![Simulations](https://img.shields.io/badge/simulations-11%20interactive-brightgreen.svg)
![Cost](https://img.shields.io/badge/cost-%E2%82%B937,500-orange.svg)

---

## 🎯 What This Project Does

This repository contains an end-to-end engineering blueprint, firmware, wiring schematics, and interactive simulations for a 2-floor (~2000 sq ft) whole-home automation system using:

- **ESP32 / ESP8266** distributed microcontrollers across 8 logical zones
- **Old PC / laptop** running Ubuntu Server LTS + Home Assistant Core + Mosquitto MQTT + Node-RED + Frigate NVR
- **Detached 2-Way Wall Switch Sync** allowing physical wall switches to work seamlessly alongside automations
- **Auto-Off Vacancy Intelligence** switching off fans and lights when rooms are unoccupied
- **Scrap Reuse** (repurposed smartphones, old routers as OpenWRT mesh repeaters, ATX power supplies)
- **Safety Certified Parts Only** for high-voltage mains (230V AC 50Hz), gas solenoids, and water pumps
- **RC Snubber Networks** to eliminate ceiling fan motor inductive kickback

---

## 📋 Features & Simulation Coverage (11 Testbeds)

| # | System Feature | Interactive Wokwi Simulation | Status |
|:---:|---|---|:---:|
| **01** | PIR Motion Auto-Lighting | [`simulations/01_pir_motion_light/`](file:///simulations/01_pir_motion_light/) | ✅ Functional |
| **02** | Climate & Fan Hysteresis | [`simulations/02_dht22_climate/`](file:///simulations/02_dht22_climate/) | ✅ Functional |
| **03** | Garden Auto-Watering & Anti-Flood | [`simulations/03_soil_moisture_pump/`](file:///simulations/03_soil_moisture_pump/) | ✅ Functional |
| **04** | Kitchen Gas Leak & Auto Shutoff | [`simulations/04_gas_leak/`](file:///simulations/04_gas_leak/) | ✅ Functional |
| **05** | Water Tank Level & Dry-Run Protection | [`simulations/05_water_tank/`](file:///simulations/05_water_tank/) | ✅ Functional |
| **06** | Reed Switch Perimeter Security | [`simulations/06_reed_door/`](file:///simulations/06_reed_door/) | ✅ Functional |
| **07** | Stepper Motorized Curtains | [`simulations/07_stepper_curtain/`](file:///simulations/07_stepper_curtain/) | ✅ Functional |
| **08** | **Smart Room Fan & Light Auto-Switch** | [`simulations/08_smart_room_light_fan_auto_switch/`](file:///simulations/08_smart_room_light_fan_auto_switch/) | ✅ **Functional** |
| **09** | **Mains Energy Monitor & Load Shedder** | [`simulations/09_energy_monitor_load_shedding/`](file:///simulations/09_energy_monitor_load_shedding/) | ✅ **Functional** |
| **10** | **Indoor Air Quality & Auto Exhaust** | [`simulations/10_air_quality_auto_exhaust/`](file:///simulations/10_air_quality_auto_exhaust/) | ✅ **Functional** |
| **11** | **Smart Doorbell, Panic & Fall Alarm** | [`simulations/11_smart_doorbell_panic_fall/`](file:///simulations/11_smart_doorbell_panic_fall/) | ✅ **Functional** |

---

## 💰 Cost Comparison

- **Total DIY Prototype Cost:** ₹37,500 (~$450 USD) for 15 nodes across 2 floors
- **Commercial Equivalent (Control4 / Crestron / Schneider):** ₹2,00,000+ ($2,400+ USD)
- **Net Cost Savings:** > 80%

---

## 🚀 Quick Start Guide

1. **Read Safety First:** Review [09_Safety_Guidelines.md](file:///09_Safety_Guidelines.md).
2. **Review Real-Home Switchboard Wiring:** Follow [18_Real_Home_Installation_Switchboard_Wiring_Guide.md](file:///18_Real_Home_Installation_Switchboard_Wiring_Guide.md).
3. **Run Interactive Simulations:** Choose any folder in `simulations/` and run in [wokwi.com](https://wokwi.com) or VS Code.
4. **Set Up Local Hub:** Follow [01_System_Architecture_and_Hub_Setup.md](file:///01_System_Architecture_and_Hub_Setup.md).
5. **Procure Hardware:** Use verified Indian vendor links in [10_Procurement_India_Links.md](file:///10_Procurement_India_Links.md).
6. **Flash Nodes:** Deploy tested YAML configurations from [06_ESPHome_YAML_Configurations_All_Nodes.md](file:///06_ESPHome_YAML_Configurations_All_Nodes.md).

---

## 📁 Repository Document Index

| File | Purpose & Description |
|---|---|
| [`00_Project_Master_Plan.md`](file:///00_Project_Master_Plan.md) | Whole-house vision, scope, milestones & commercialization roadmap |
| [`01_System_Architecture_and_Hub_Setup.md`](file:///01_System_Architecture_and_Hub_Setup.md) | Ubuntu server hub, Docker stack, static IP map & mesh WiFi |
| [`02_Node_Clubbing_BOM_and_Cost.md`](file:///02_Node_Clubbing_BOM_and_Cost.md) | Node zone clubbing, GPIO assignments & complete BOM |
| [`03_Scrap_Reuse_Guide.md`](file:///03_Scrap_Reuse_Guide.md) | Repurposing scrap PCs, routers, webcams & ATX power supplies |
| [`04_Simulation_Guide_Wokwi.md`](file:///04_Simulation_Guide_Wokwi.md) | Wokwi simulation guide & testing methodology |
| [`05_Sensor_Actuator_Specifications.md`](file:///05_Sensor_Actuator_Specifications.md) | Component pinouts, electrical ratings & sensor characteristics |
| [`06_ESPHome_YAML_Configurations_All_Nodes.md`](file:///06_ESPHome_YAML_Configurations_All_Nodes.md) | Complete production-ready ESPHome YAML firmware |
| [`07_Home_Assistant_Configuration_and_Dashboard.md`](file:///07_Home_Assistant_Configuration_and_Dashboard.md) | HA dashboards, Lovelace UI cards & MQTT entity configs |
| [`08_Node_RED_Automations.md`](file:///08_Node_RED_Automations.md) | Complex stateful automation flows & safety interlocks |
| [`09_Safety_Guidelines.md`](file:///09_Safety_Guidelines.md) | ⚠️ Electrical 230V AC, gas, water & Li-ion battery safety rules |
| [`10_Procurement_India_Links.md`](file:///10_Procurement_India_Links.md) | Direct procurement links for Indian stores (Robu, Evelta, Amazon) |
| [`11_Testing_Checklist.md`](file:///11_Testing_Checklist.md) | 4-phase testing & 30-day commissioning checklist |
| [`12_DIY_vs_ReadyMade_Recommendations.md`](file:///12_DIY_vs_ReadyMade_Recommendations.md) | Build vs buy decisions matrix |
| [`13_Cost_Estimate_Summary.md`](file:///13_Cost_Estimate_Summary.md) | Detailed cost breakdown by zone & component |
| [`14_Commercialization_PCB_Design_and_Selling.md`](file:///14_Commercialization_PCB_Design_and_Selling.md) | EasyEDA / JLCPCB custom PCB roadmap & pricing models |
| [`15_README_For_Each_Node.md`](file:///15_README_For_Each_Node.md) | Node-by-node quick reference & troubleshooting |
| [`16_Learning_Path_and_References.md`](file:///16_Learning_Path_and_References.md) | ELI5 fundamentals, protocols & reference links |
| [`17_GitHub_Repository_Structure_and_README.md`](file:///17_GitHub_Repository_Structure_and_README.md) | Repository organization & engineering standards |
| [`18_Real_Home_Installation_Switchboard_Wiring_Guide.md`](file:///18_Real_Home_Installation_Switchboard_Wiring_Guide.md) | **[NEW] Modular switchboard retrofit, 2-way sync & snubbers** |
| [`AUDIT/00_MASTER_AUDIT.md`](file:///AUDIT/00_MASTER_AUDIT.md) | Initial engineering pre-build audit report |
| [`AUDIT/01_PROTOTYPE_PHOTO_MASTER_PROMPT.md`](file:///AUDIT/01_PROTOTYPE_PHOTO_MASTER_PROMPT.md) | Ready-to-paste AI image generation prompts for visual renders |
| [`AUDIT/02_COMPLETE_MASTER_POST_AUDIT.md`](file:///AUDIT/02_COMPLETE_MASTER_POST_AUDIT.md) | **[NEW] Master complete post-audit & verification sign-off** |

---

## 📸 Wiring Schematics & Visual Architecture

Crisp vector schematics are included in `photos/wiring/`:
- **Whole-House Architecture:** [`photos/wiring/whole_home_system_architecture.svg`](file:///photos/wiring/whole_home_system_architecture.svg)
- **Room Switchboard Retrofit:** [`photos/wiring/08_smart_room_fan_light_switchboard.svg`](file:///photos/wiring/08_smart_room_fan_light_switchboard.svg)

---

## ⚠️ Mandatory Safety Disclaimer

This project interfaces directly with **230V AC mains electricity**, **LPG gas lines**, and **pressurized water lines**.
- Always disconnect the primary MCB before opening any switchboard.
- Use certified, optocoupler-isolated relay modules with RC snubber protection.
- Ensure all gas and water shutoff valves are certified with fail-safe closure mechanisms.

---

## 📜 License
MIT License. Free to use, modify, and commercialize with attribution.
