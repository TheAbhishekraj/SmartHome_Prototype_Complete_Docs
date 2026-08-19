# 12_DIY_vs_ReadyMade_Recommendations.md
# SmartHome Prototype — Build vs Buy Analysis

**Version:** 1.0 | **Date:** August 2026

---

## Decision Matrix

| Automation | DIY Cost | Ready-Made Cost | DIY Difficulty | Recommendation | Notes |
|------------|----------|-----------------|----------------|----------------|-------|
| **PIR Motion Light** | ₹300 | ₹800-1500 | Easy | **DIY** | Simple, reliable |
| **Garden Watering** | ₹800 | ₹2000-4000 | Medium | **DIY** | Custom scheduling |
| **Gas Leak Detection** | ₹1500 | ₹3000-6000 | Hard | **DIY + Certified Valve** | Sensor DIY, valve certified new |
| **Smoke Detection** | ₹400 | ₹500-1500 | Easy | **Buy** (Kidde/Honeywell) | Certified, insurance-approved |
| **Water Tank Auto-Pump** | ₹1200 | ₹3000-8000 | Medium | **DIY** | Float switches are simple |
| **AC/Fan IR Control** | ₹400 | ₹1500-3000 | Easy | **DIY** | Learn codes once |
| **Curtain Motor** | ₹1500 | ₹5000-15000 | Medium | **DIY** | Stepper + 3D printed parts |
| **Security Camera** | ₹700 | ₹2000-5000 | Medium | **DIY** (ESP32-CAM) | For basic; buy Reolink for 24/7 |
| **Video Doorbell** | ₹800 | ₹3000-10000 | Medium | **DIY** | ESP32-CAM sufficient |
| **Intrusion Alarm** | ₹1500 | ₹5000-15000 | Medium | **DIY** | Custom zones |
| **Robot Vacuum** | N/A | ₹15000-40000 | N/A | **Buy** (Mi/Roborock) | Cannot DIY competitively |
| **Air Quality** | ₹3500 | ₹5000-12000 | Medium | **DIY** | PMS5003 + MH-Z19B accurate |
| **Aquarium Control** | ₹1200 | ₹3000-8000 | Easy | **DIY** | Simple timers + sensors |
| **Energy Monitor** | ₹1000 | ₹3000-8000 | Hard | **DIY** (PZEM-004T) | Non-invasive, safe |
| **Fall Detection** | ₹800 | ₹15000-50000 (Aqara FP2) | Medium | **DIY** (LD2410B) | 1/20th the cost |
| **Smart Lock** | ₹2000 | ₹5000-20000 | Hard | **Buy** (Yale/Atomberg) | Security-critical, buy certified |

---

## When to DIY

**DIY when:**
- Cost savings >60%
- Component is simple (sensor + relay)
- You need custom logic (Node-RED)
- Safety is NOT life-critical
- You enjoy building and learning
- Commercial product doesn't exist for your need

## When to Buy

**Buy when:**
- Life safety depends on it (certified smoke alarm)
- Insurance requires certification
- Warranty and support needed
- Time is more valuable than money
- Product is cheaper than parts (economies of scale)
- Aesthetics matter (smart locks, wall switches)

---

## Hybrid Approach (Recommended)

| System | DIY Component | Buy Component |
|--------|-------------|---------------|
| Kitchen Safety | ESP32 + MQ-6 sensor | Certified gas solenoid valve |
| Water Management | ESP32 + float switches | Certified contactor, pressure switch |
| Security | ESP32 + reed switches + PIR | Certified siren, commercial IP camera backup |
| Climate | ESP32 + IR blaster | Nothing — DIY is best |
| Electrical | ESP32 + PZEM-004T | Certified contactor for cutoff |

---

*End of 12_DIY_vs_ReadyMade_Recommendations.md*
