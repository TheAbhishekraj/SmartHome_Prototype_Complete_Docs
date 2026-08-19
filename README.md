# 🏠 SmartHome Prototype — Whole-Home Automation for 2-Floor Flat

> **From scrap to smart — a complete, local, privacy-first home automation system built with ESP32, Home Assistant, and Indian market components.**

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Status](https://img.shields.io/badge/status-prototype-green.svg)
![Cost](https://img.shields.io/badge/cost-%E2%82%B937,500-orange.svg)

## 🎯 What This Project Does

This repository contains everything needed to build a complete whole-home automation system for a 2-floor, ~2000 sq ft flat using:

- **ESP32/ESP8266** microcontrollers as wireless sensor nodes
- **Old PC/laptop** as the central Home Assistant hub
- **Scrap reuse** (old phones, routers, ATX PSUs) to minimize cost
- **New certified components** for all safety-critical systems (gas, water, mains)

## 📋 What's Included

| Feature | Status |
|---------|--------|
| Garden auto-watering & rain protection | ✅ |
| Kitchen gas leak & smoke detection | ✅ |
| Water tank auto-fill with dry-run protection | ✅ |
| Motion-activated lights in every room | ✅ |
| Climate control (fan/AC IR blaster) | ✅ |
| Security cameras & intrusion alarm | ✅ |
| Video doorbell | ✅ |
| Air quality monitoring | ✅ |
| Aquarium automation | ✅ |
| Whole-house electrical monitoring | ✅ |
| Panic button & fall detection | ✅ |

## 💰 Cost

- **Total prototype cost:** ₹37,500 (~$450)
- **vs. commercial systems:** ₹2,00,000+ ($2,400+)
- **Savings:** 80%+

## 🚀 Quick Start

1. **Read** `docs/09_Safety_Guidelines.md` FIRST
2. **Set up hub:** Follow `docs/01_System_Architecture_and_Hub_Setup.md`
3. **Order parts:** Use `docs/10_Procurement_India_Links.md`
4. **Simulate:** Follow `docs/04_Simulation_Guide_Wokwi.md`
5. **Build:** Start with safety nodes (kitchen, water, fire)
6. **Configure:** Flash YAML from `firmware/` folder

## 📁 Documentation

All 18 detailed documentation files are in `docs/`:

| File | Purpose |
|------|---------|
| 00_Project_Master_Plan.md | Vision, scope, roadmap |
| 01_System_Architecture_and_Hub_Setup.md | Hub, network, remote access |
| 02_Node_Clubbing_BOM_and_Cost.md | Complete parts list |
| 03_Scrap_Reuse_Guide.md | Repurpose old electronics |
| 04_Simulation_Guide_Wokwi.md | Test before building |
| 05_Sensor_Actuator_Specifications.md | Datasheets & pinouts |
| 06_ESPHome_YAML_Configurations_All_Nodes.md | All firmware |
| 07_Home_Assistant_Configuration_and_Dashboard.md | Dashboard setup |
| 08_Node_RED_Automations.md | Complex automation logic |
| 09_Safety_Guidelines.md | ⚠️ MANDATORY READ |
| 10_Procurement_India_Links.md | Where to buy in India |
| 11_Testing_Checklist.md | Commissioning guide |
| 12_DIY_vs_ReadyMade_Recommendations.md | Build vs buy |
| 13_Cost_Estimate_Summary.md | Detailed costing |
| 14_Commercialization_PCB_Design_and_Selling.md | Business roadmap |
| 15_README_For_Each_Node.md | Per-node tuning guides |
| 16_Learning_Path_and_References.md | ELI5 explanations |
| 17_GitHub_Repository_Structure_and_README.md | This file |

## ⚠️ Safety First

This project involves **230V AC mains voltage**, **flammable gas**, and **pressurized water**.

- Read `docs/09_Safety_Guidelines.md` completely before starting
- Use certified components for all safety-critical parts
- Consult licensed electricians for mains work
- Consult licensed plumbers for gas/water valves

**The authors are not responsible for injury or damage from improper installation.**

## 🤝 Contributing

This is a personal prototype project. Suggestions and improvements welcome via Issues.

## 📜 License

MIT License — see LICENSE file. Includes safety disclaimer.

## 🙏 Acknowledgments

- Home Assistant community
- ESPHome developers
- Node-RED contributors
- Open-source hardware movement

---

*Source: [TheAbhishekraj/SmartHome_Prototype_Complete_Docs](https://github.com/TheAbhishekraj/SmartHome_Prototype_Complete_Docs)*

