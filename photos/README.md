# 📸 Photos & Wiring-Diagram Visual Schematics

This directory contains **publication-grade vector SVG wiring diagrams** and visual schematics for every simulated and commercial project in the repository, along with photographic build guidelines.

---

## 🎨 Complete Vector Schematics Index

| Schematic File | Domain / System | Description & Components |
|---|---|---|
| [`whole_home_system_architecture.svg`](file:///photos/wiring/whole_home_system_architecture.svg) | Whole-House (2 Floors) | Central PC hub, Mosquitto MQTT, Home Assistant, OpenWRT mesh WiFi, 4 primary zones. |
| [`01_pir_motion_light.svg`](file:///photos/wiring/01_pir_motion_light.svg) | Sim 01 / Lighting | AM312/HC-SR501 PIR sensor + 5V opto-relay + 30s vacancy auto-off logic. |
| [`02_dht22_climate_fan.svg`](file:///photos/wiring/02_dht22_climate_fan.svg) | Sim 02 / Climate | DHT22 temperature/humidity sensor + ceiling fan relay with 1.5°C anti-chatter hysteresis. |
| [`03_soil_moisture_pump.svg`](file:///photos/wiring/03_soil_moisture_pump.svg) | Sim 03 / Garden | Capacitive soil sensor + 12V garden pump relay + anti-flood timeout protection. |
| [`04_kitchen_gas_safety.svg`](file:///photos/wiring/04_kitchen_gas_safety.svg) | Sim 04 / Kitchen Safety | MQ-6 LPG sensor + exhaust fan relay + fail-safe gas solenoid shutoff + 110dB siren. |
| [`05_water_tank_ultrasonic.svg`](file:///photos/wiring/05_water_tank_ultrasonic.svg) | Sim 05 / Water Management | HC-SR04 ultrasonic level sensor + pump contactor + sump dry-run cutoff float. |
| [`06_reed_door_security.svg`](file:///photos/wiring/06_reed_door_security.svg) | Sim 06 / Perimeter Security | Magnetic reed switch with debounced internal pull-up + intrusion alarm dispatch. |
| [`07_stepper_curtain.svg`](file:///photos/wiring/07_stepper_curtain.svg) | Sim 07 / Curtains | A4988 stepper driver + NEMA-17/28BYJ-48 motorized curtain controller (authorized pin map). |
| [`08_smart_room_fan_light_switchboard.svg`](file:///photos/wiring/08_smart_room_fan_light_switchboard.svg) | Sim 08 / Switchboards | Modular switchboard retrofit + 2-way manual wall switch sync + PIR/LDR + RC snubber. |
| [`09_energy_monitor_load_shedding.svg`](file:///photos/wiring/09_energy_monitor_load_shedding.svg) | Sim 09 / Mains Energy | SCT-013 / PZEM-004T CT sensor + 16x2 I2C LCD + automated peak load shedding contactor. |
| [`10_air_quality_auto_exhaust.svg`](file:///photos/wiring/10_air_quality_auto_exhaust.svg) | Sim 10 / Ventilation | MQ-135 air quality sensor + 3-stage LEDs + auto exhaust fan purge cycle. |
| [`11_smart_doorbell_panic_fall.svg`](file:///photos/wiring/11_smart_doorbell_panic_fall.svg) | Sim 11 / Personal Safety | 2-tone melodic visitor doorbell + latching emergency panic button + fall sensor + reset switch. |
| [`12_commercial_shop_automation.svg`](file:///photos/wiring/12_commercial_shop_automation.svg) | Commercial / Retail Shops | 25A glow-sign contactor + pharmacy deep-freezer temperature logger + armored shutter alarm. |

---

## 🛠️ Step-by-Step Making Manual & Hardware Assembly
For detailed soldering, wire gauge sizing (0.5mm² vs 2.5mm²), perfboard creepage isolation slots, and pre-commissioning testing, consult:  
👉 [`19_Hardware_Fabrication_and_Making_Manual.md`](file:///19_Hardware_Fabrication_and_Making_Manual.md)

---

## ⚡ Industry Standards & AC Safety Compliance
For Bureau of Indian Standards (IS 732, IS 13947) and International (IEC 60669-2-1, IEC 60947) electrical safety codes, see:  
👉 [`21_Industry_Standards_IS_IEC_Compliance_and_AC_Safety.md`](file:///21_Industry_Standards_IS_IEC_Compliance_and_AC_Safety.md)