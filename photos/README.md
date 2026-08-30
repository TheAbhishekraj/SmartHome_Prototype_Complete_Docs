# 📸 Photos & Wiring-Diagram Images

This folder is reserved for **actual build photos** and **generated wiring-diagram images** for the SmartHome Prototype.

> **Why it matters:** visual references help you (and anyone installing) wire each node correctly and document the build for troubleshooting and the commercialization roadmap.

## What to put here
| Folder / file | Content | Status |
|---------------|---------|--------|
| `wiring/` | Rendered wiring diagrams (PNG/JPG) per node, from the `simulations/WIRING.md` ASCII references | ⏳ to add |
| `nodes/` | Real photos of each built node (breadboard → final enclosure) | ⏳ after building |
| `panel/` | Hub + electrical panel installation photos | ⏳ |
| `hero.png` | Product-kit / hero shot for the README (optional) | ⏳ |

## How to create wiring-diagram images (no manual drawing)
Use the helper: **`AUDIT/01_PROTOTYPE_PHOTO_MASTER_PROMPT.md`** — it contains ready-to-paste AI image prompts (one per node + a schematic-style prompt) that match the exact pins in `simulations/WIRING.md`. Paste the relevant block into any image generator (DALL·E, Midjourney, StabLe Diffusion, etc.) to get a visual render, then drop the PNG/JPG into `wiring/`.

## Suggested naming
Match the simulation/node so the wiring diagram is easy to find:
```
wiring/01_pir_motion_light.png
wiring/02_dht22_climate.png
wiring/03_garden_pump.png
wiring/04_kitchen_gas.png
wiring/05_water_tank.png
wiring/06_reed_door.png
wiring/07_stepper_curtain.png
nodes/node-b1-kitchen-safety.jpg
```

## Checklist when you photograph a real node
- [ ] Good lighting, in-focus, close enough to read wire labels
- [ ] Show the ESP32 + module + wire color coding clearly
- [ ] Include a label showing the node name (e.g. `NODE-B1`)
- [ ] Add a photo of the inside of the enclosure and the mounting location
- [ ] Upload after each build so the repo stays current

*End of photos README.*