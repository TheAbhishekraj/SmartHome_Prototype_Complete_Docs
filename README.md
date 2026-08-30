# 🏠 SmartHome & Commercial IoT Prototype — Whole-House & Retail Automation

> **From scrap to smart — a complete, local, privacy-first IoT automation system built with ESP32 microcontrollers, Home Assistant, 11 interactive Wokwi simulations, modular switchboard retrofits, and commercial retail shop extensions.**

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Status](https://img.shields.io/badge/status-production--ready-green.svg)
![Simulations](https://img.shields.io/badge/simulations-11%20interactive-brightgreen.svg)
![Standards](https://img.shields.io/badge/standards-IS%20732%20%7C%20IEC%2060669-blue.svg)
![Cost](https://img.shields.io/badge/cost-%E2%82%B937,500-orange.svg)

---

## 🌐 Whole-House Distributed Architecture

![Whole House System Architecture](https://raw.githubusercontent.com/TheAbhishekraj/SmartHome_Prototype_Complete_Docs/master/photos/wiring/whole_home_system_architecture.svg)

> **🖼️ Complete Visual Schematics Gallery:** Browse all 13 interactive SVG schematics in the [**Photos & Visual Schematics Directory**](https://github.com/TheAbhishekraj/SmartHome_Prototype_Complete_Docs/tree/master/photos).

---

## 📋 Features & Simulation Coverage (11 Testbeds + Commercial)

| # | System Feature | Interactive Wokwi Simulation | Visual SVG Schematic |
|:---:|---|---|---|
| **01** | PIR Motion Auto-Lighting | [`simulations/01_pir_motion_light/`](file:///simulations/01_pir_motion_light/) | [`01_pir_motion_light.svg`](file:///photos/wiring/01_pir_motion_light.svg) |
| **02** | Climate & Fan Hysteresis | [`simulations/02_dht22_climate/`](file:///simulations/02_dht22_climate/) | [`02_dht22_climate_fan.svg`](file:///photos/wiring/02_dht22_climate_fan.svg) |
| **03** | Garden Auto-Watering & Anti-Flood | [`simulations/03_soil_moisture_pump/`](file:///simulations/03_soil_moisture_pump/) | [`03_soil_moisture_pump.svg`](file:///photos/wiring/03_soil_moisture_pump.svg) |
| **04** | Kitchen Gas Leak & Auto Shutoff | [`simulations/04_gas_leak/`](file:///simulations/04_gas_leak/) | [`04_kitchen_gas_safety.svg`](file:///photos/wiring/04_kitchen_gas_safety.svg) |
| **05** | Water Tank Level & Dry-Run Protection | [`simulations/05_water_tank/`](file:///simulations/05_water_tank/) | [`05_water_tank_ultrasonic.svg`](file:///photos/wiring/05_water_tank_ultrasonic.svg) |
| **06** | Reed Switch Perimeter Security | [`simulations/06_reed_door/`](file:///simulations/06_reed_door/) | [`06_reed_door_security.svg`](file:///photos/wiring/06_reed_door_security.svg) |
| **07** | Stepper Motorized Curtains | [`simulations/07_stepper_curtain/`](file:///simulations/07_stepper_curtain/) | [`07_stepper_curtain.svg`](file:///photos/wiring/07_stepper_curtain.svg) |
| **08** | **Smart Room Fan & Light Auto-Switch** | [`simulations/08_smart_room_light_fan_auto_switch/`](file:///simulations/08_smart_room_light_fan_auto_switch/) | [`08_smart_room_fan_light_switchboard.svg`](file:///photos/wiring/08_smart_room_fan_light_switchboard.svg) |
| **09** | **Mains Energy Monitor & Load Shedder** | [`simulations/09_energy_monitor_load_shedding/`](file:///simulations/09_energy_monitor_load_shedding/) | [`09_energy_monitor_load_shedding.svg`](file:///photos/wiring/09_energy_monitor_load_shedding.svg) |
| **10** | **Indoor Air Quality & Auto Exhaust** | [`simulations/10_air_quality_auto_exhaust/`](file:///simulations/10_air_quality_auto_exhaust/) | [`10_air_quality_auto_exhaust.svg`](file:///photos/wiring/10_air_quality_auto_exhaust.svg) |
| **11** | **Smart Doorbell, Panic & Fall Alarm** | [`simulations/11_smart_doorbell_panic_fall/`](file:///simulations/11_smart_doorbell_panic_fall/) | [`11_smart_doorbell_panic_fall.svg`](file:///photos/wiring/11_smart_doorbell_panic_fall.svg) |
| **12** | **Commercial Shop & Heavy Appliances** | *Full Design & Wiring Specification* | [`12_commercial_shop_automation.svg`](file:///photos/wiring/12_commercial_shop_automation.svg) |

---

## 💰 Cost Comparison

- **Total DIY Prototype Cost:** ₹37,500 (~$450 USD) for 15 nodes across 2 floors
- **Commercial Equivalent (Control4 / Crestron / Schneider):** ₹2,00,000+ ($2,400+ USD)
- **Net Cost Savings:** > 80%

---

## 📁 Complete Repository Document Index

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
| [`18_Real_Home_Installation_Switchboard_Wiring_Guide.md`](file:///18_Real_Home_Installation_Switchboard_Wiring_Guide.md) | Modular switchboard retrofit, 2-way sync & snubbers |
| [`19_Hardware_Fabrication_and_Making_Manual.md`](file:///19_Hardware_Fabrication_and_Making_Manual.md) | **[NEW] Step-by-step soldering, perfboard assembly & making manual** |
| [`20_Commercial_Shop_and_Appliance_Automation_Guide.md`](file:///20_Commercial_Shop_and_Appliance_Automation_Guide.md) | **[NEW] Retail shop, cold-chain, glow-sign & heavy appliance guide** |
| [`21_Industry_Standards_IS_IEC_Compliance_and_AC_Safety.md`](file:///21_Industry_Standards_IS_IEC_Compliance_and_AC_Safety.md) | **[NEW] IS 732, IS 13947 & IEC 60669 electrical compliance** |
| [`AUDIT/00_MASTER_AUDIT.md`](file:///AUDIT/00_MASTER_AUDIT.md) | Initial engineering pre-build audit report |
| [`AUDIT/01_PROTOTYPE_PHOTO_MASTER_PROMPT.md`](file:///AUDIT/01_PROTOTYPE_PHOTO_MASTER_PROMPT.md) | Ready-to-paste AI image generation prompts for visual renders |
| [`AUDIT/02_COMPLETE_MASTER_POST_AUDIT.md`](file:///AUDIT/02_COMPLETE_MASTER_POST_AUDIT.md) | Master complete post-audit & verification sign-off |

---

## ⚡ 230V AC Safety & IS/IEC Standards Compliance

1. **Galvanic Isolation:** All mains relays feature optocouplers with 2.5kV isolation and $\ge 6.3\text{mm}$ creepage clearance.
2. **Surge Suppression:** MOV `14D471K` surge arrestors protect against Indian grid voltage spikes.
3. **Inductive Snubber Networks:** RC snubbers (0.1µF 400V + 100Ω) across all ceiling fan contacts prevent motor back-EMF arcing.
4. **Code Compliance:** Designed in accordance with **IS 732 (2019)**, **IS 13947**, and **IEC 60669-2-1**.

---

## 📜 License
MIT License. Free to use, modify, and commercialize with attribution.
