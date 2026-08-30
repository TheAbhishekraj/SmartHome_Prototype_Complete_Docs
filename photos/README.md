# 📸 Photos & Wiring-Diagram Images

This folder contains **rendered wiring schematics**, **whole-home system architecture diagrams**, and guidelines for photographing physical breadboards and switchboard retrofits.

---

## Included Vector Schematics & Diagrams

| Schematic File | Domain / Node | Description |
|---|---|---|
| **`wiring/whole_home_system_architecture.svg`** | Whole House (2 Floors) | High-level system architecture showing PC hub, Mosquitto, Home Assistant, OpenWRT mesh, and all 4 main functional zones. |
| **`wiring/08_smart_room_fan_light_switchboard.svg`** | Room Nodes (NODE-D1/D2/D3/D4) | Detailed wiring diagram for 230V AC Indian modular switchboards, Hi-Link SMPS, detached 2-way manual switch sync, PIR/LDR sensors, and RC snubbers. |

---

## Master AI Prompt for Additional Photorealistic Renders
To generate photo-realistic 3D prototypes or blueprint visual renders, use the prompt catalog located in:  
👉 **`AUDIT/01_PROTOTYPE_PHOTO_MASTER_PROMPT.md`**

---

## Guidelines for Real Hardware Build Photos
When deploying nodes in your home, add high-resolution photos into subdirectories:
- `nodes/`: Enclosure assembly and sensor mounting (e.g. `nodes/living_room_switchboard_retrofit.jpg`).
- `panel/`: Distribution board contactors, master emergency cutoff, and central PC hub mounting.