# 03_Scrap_Reuse_Guide.md
# SmartHome Prototype — Scrap Reuse & E-Waste Repurposing Guide

**Version:** 1.0 | **Date:** August 2026

---

## Table of Contents
1. [Philosophy](#1-philosophy)
2. [Old PC / Laptop → Home Assistant Hub](#2-old-pc--laptop--home-assistant-hub)
3. [ATX Power Supply → 5V / 12V DC Rail](#3-atx-power-supply--5v--12v-dc-rail)
4. [Old Smartphones → Wall Dashboards & Sensors](#4-old-smartphones--wall-dashboards--sensors)
5. [Old WiFi Routers → Mesh Access Points](#5-old-wifi-routers--mesh-access-points)
6. [Old Speakers → Smart Announcement System](#6-old-speakers--smart-announcement-system)
7. [Old Webcams → IP Cameras](#7-old-webcams--ip-cameras)
8. [Old Laptop Batteries → 18650 Cell Harvesting](#8-old-laptop-batteries--18650-cell-harvesting)
9. [Old USB Cables & Chargers → Power Distribution](#9-old-usb-cables--chargers--power-distribution)
10. [Old Mouse/Keyboard → Input Devices](#10-old-mousekeyboard--input-devices)
11. [Old Hard Drives → NAS / Backup Storage](#11-old-hard-drives--nas--backup-storage)
12. [Salvage Safety Rules](#12-salvage-safety-rules)
13. [What NOT to Reuse](#13-what-not-to-reuse)

---

## 1. Philosophy

**"The best component is the one you already own."**

This project is designed to minimize e-waste and cost by repurposing common household scrap. However, **safety-critical parts (mains voltage, gas valves, water valves) MUST be new and certified.**

**Reuse Hierarchy:**
1. **Direct reuse** — works as-is with minimal config (old PC, router, phone)
2. **Repurpose with simple mod** — needs basic soldering or flashing (ATX PSU, webcam)
3. **Component harvest** — extract useful parts (18650 cells, motors, relays)
4. **Buy new** — only for safety-critical or unavailable items

---

## 2. Old PC / Laptop → Home Assistant Hub

### What You Need
- Any PC from 2012+ with 4GB RAM
- 128GB+ SSD (SATA or mSATA)
- Ethernet port

### Preparation Steps
```bash
# 1. Backup any personal data from old PC
# 2. Boot from Ubuntu Server USB
# 3. During install, choose "Erase disk" for dedicated automation PC
# 4. If keeping Windows dual-boot: shrink partition, install Ubuntu alongside

# Laptop-specific advantages:
# - Built-in battery = free UPS (2-4 hours backup)
# - Built-in WiFi = backup connectivity if Ethernet fails
# - Lower power consumption than desktop (~15W vs 60W)

# Desktop-specific advantages:
# - More SATA ports for multiple HDDs (NVR storage)
# - PCIe slots for Coral TPU or additional NICs
# - Better cooling for 24/7 operation
```

### Power Optimization (Laptop)
```bash
# Keep laptop lid closed but running
sudo nano /etc/systemd/logind.conf
# Set: HandleLidSwitch=ignore
sudo systemctl restart systemd-logind

# Disable screen (save power)
sudo systemctl set-default multi-user.target  # No GUI
# Or if using GUI: xset dpms force off

# CPU governor to powersave
sudo apt install cpufrequtils
sudo systemctl enable cpufrequtils
sudo nano /etc/default/cpufrequtils
# GOVERNOR="powersave"
```

### Power Optimization (Desktop)
```bash
# Remove GPU if using integrated graphics
# Disconnect unused fans
# Use 80+ Bronze PSU minimum
# Expected power: 25-40W idle for i5 desktop
```

**Cost Saved:** ₹8,000–₹15,000 (vs. buying NUC or server)

---

## 3. ATX Power Supply → 5V / 12V DC Rail

### How ATX PSU Works
An old 300W–450W ATX PSU provides:
- **+3.3V** (orange wires) — not used
- **+5V** (red wires) — ESP32, sensors, relays, USB devices
- **+12V** (yellow wires) — Motors, solenoids, sirens, fans
- **GND** (black wires) — Common ground

### Conversion Steps
```
1. SAFETY FIRST: Unplug PSU, press power button to discharge capacitors
2. Wait 10 minutes after unplugging (capacitors hold charge)
3. Open PSU case (voids warranty — only do on old/scrap units)
4. Identify wire colors:
   - RED = +5V
   - YELLOW = +12V
   - BLACK = GND
   - GREEN = PS_ON (must connect to GND to turn on)
   - GREY = PWR_OK (optional)
5. Cut connectors off, strip wires, bundle by color
6. Connect GREEN wire to any BLACK wire (this turns PSU ON)
7. Add a switch between GREEN and BLACK for manual control
8. Add a 5A fuse on +5V line and +12V line
9. Mount in ventilated enclosure
```

### Wiring Diagram
```
ATX PSU (300W)
┌─────────────────────────────────────┐
│  GREEN ──┬── SWITCH ──┬── BLACK    │
│          │            │             │
│  RED ────┼──[FUSE 5A]─┼── +5V Rail │
│  (×8)    │            │   Terminal  │
│          │            │   Block     │
│  YELLOW ─┼──[FUSE 5A]─┼── +12V Rail│
│  (×4)    │            │   Terminal  │
│          │            │   Block     │
│  BLACK ──┴────────────┴── GND Rail  │
│  (×12)                              │
└─────────────────────────────────────┘
```

### Expected Output
| Rail | Current Capacity | Usable For |
|------|-----------------|------------|
| +5V | 15–20A | 15+ ESP32 nodes, sensors, relays |
| +12V | 10–15A | Motors, solenoids, sirens, pumps |

**Cost Saved:** ₹2,000–₹3,000 (vs. buying multiple SMPS adapters)

**WARNING:** Do NOT open PSU if you are not comfortable with high voltage. Capacitors can hold lethal charge. Use a "dummy load" resistor (10Ω 10W) on 5V rail for stability.

---

## 4. Old Smartphones → Wall Dashboards & Sensors

### Use Case 1: Wall-Mounted Home Assistant Dashboard

**Phones Needed:** Any Android 5.0+ with working screen and WiFi

**Setup:**
1. Factory reset phone
2. Install "Home Assistant Companion" app from Play Store
3. Connect to WiFi (SmartHome_IoT network)
4. Open HA URL: `http://192.168.1.10:8123`
5. Log in with family member account
6. Enable: Settings → Companion App → Keep Screen On (while charging)
7. Set dashboard as default view

**Mounting:**
- 3D print wall mount OR use magnetic car phone holder
- Route USB cable through wall (or use command strip cable clips)
- Old phone charger = permanent power

**Dashboard Apps:**
- Fully Kiosk Browser (better than HA app for dedicated display)
- WallPanel (open source alternative)

**Cost Saved:** ₹3,000–₹8,000 per tablet (vs. buying wall tablets)

### Use Case 2: IP Camera (if phone has good camera)
Install "IP Webcam" app → RTSP stream → Frigate can consume it.

### Use Case 3: NFC Reader for Smart Door Lock
Old phone with NFC → Tasker app → HTTP request to Node-RED → Unlock door.

---

## 5. Old WiFi Routers → Mesh Access Points

### Compatible Routers
- TP-Link WR740N/WR841N
- D-Link DIR-615
- Netgear WNR series
- Any router supported by OpenWRT (check openwrt.org/toh)

### Flashing Process (TP-Link Example)
```
1. Download correct OpenWRT factory image for your model
2. Connect PC to router via Ethernet
3. Open router admin page (usually 192.168.0.1)
4. Go to System Tools → Firmware Upgrade
5. Select OpenWRT factory image, click Upgrade
6. Wait 5 minutes (DO NOT unplug)
7. Router reboots with OpenWRT at 192.168.1.1
8. SSH in: ssh root@192.168.1.1 (no password initially)
9. Set password: passwd
10. Configure as dumb AP (see File 01, Section 9)
```

### Positioning for 2-Floor Coverage
```
Ground Floor: Main Router (where internet enters)
              │
              ├── Old Router #1 (OpenWRT) ── Living Room / Center
              │     SSID: SmartHome_IoT, CH6
              │
First Floor:  ├── Old Router #2 (OpenWRT) ── Hallway
                    SSID: SmartHome_IoT, CH11
                    Connected via Ethernet backhaul (preferred)
                    OR WiFi backhaul (slower but works)
```

**Cost Saved:** ₹3,000–₹6,000 (vs. buying mesh WiFi system)

---

## 6. Old Speakers → Smart Announcement System

### Simple Version (Bluetooth)
1. Connect old Bluetooth speaker to HA hub (if hub has BT)
2. Use Home Assistant `tts.google_translate_say` service
3. Or: `tts.piper` (local, privacy-friendly)

### Advanced Version (Wired)
1. Old computer speakers with 3.5mm jack
2. USB Sound Card (₹150) if hub has no audio out
3. Connect to hub
4. Install `vlc` or `mpg123` in container
5. HA automation: Play alert sounds via shell command

### Use Cases
- "Gas leak detected in kitchen!"
- "Water tank is full. Pump stopped."
- "Intrusion detected at front door!"
- Morning alarm / scene announcements

**Cost Saved:** ₹1,500–₹3,000 (vs. buying smart speakers)

---

## 7. Old Webcams → IP Cameras

### Method: USB Webcam + MotionEyeOS or Linux
If your hub has USB ports to spare:

**Option A: MotionEye (in Docker)**
```yaml
# Add to docker-compose.yml
  motioneye:
    container_name: motioneye
    image: ccrisan/motioneye:master-amd64
    volumes:
      - ./motioneye/config:/etc/motioneye
      - ./motioneye/media:/var/lib/motioneye
    devices:
      - /dev/video0:/dev/video0
    ports:
      - "8765:8765"
    restart: unless-stopped
```

**Option B: Direct Frigate Integration**
Frigate can use USB webcams via ffmpeg:
```yaml
cameras:
  usb_cam:
    ffmpeg:
      inputs:
        - path: /dev/video0
          input_args: -f v4l2 -video_size 640x480 -framerate 10
          roles:
            - detect
```

**Cost Saved:** ₹1,500–₹4,000 per camera (vs. IP cameras)

---

## 8. Old Laptop Batteries → 18650 Cell Harvesting

### Safety Warning
**Lithium-ion cells can catch fire if punctured, shorted, or overcharged. Work in a fire-safe area. Never solder directly to cells — use spot welding or battery holders.**

### Harvesting Process
```
1. Remove battery pack from old laptop (usually 6–9 cells)
2. Carefully peel back plastic wrap (don't puncture cells)
3. Identify cell configuration (series/parallel)
4. Cut spot-welded tabs (don't short cells!)
5. Test each cell with multimeter:
   - >3.0V = likely good
   - 2.5–3.0V = may be recoverable (charge slowly)
   - <2.5V = discard (unsafe)
6. Test capacity with cheap Li-ion tester (₹300 on Amazon)
7. Keep cells >2000mAh, discard rest
```

### Use in Project
| Application | Cells Needed | Configuration |
|-------------|-------------|---------------|
| Panic button backup | 1 | Single 18650 + TP4056 + MT3608 |
| Guard robot | 2 | 2S (7.4V) or 2P (3.7V higher capacity) |
| ESP32 UPS node | 1 | Single + charging module |
| Emergency LED light | 3 | 3S (11.1V) + BMS |

**Cost Saved:** ₹100–₹150 per cell (vs. buying new 18650s)

---

## 9. Old USB Cables & Chargers → Power Distribution

### What to Keep
- **USB-A to Micro-USB:** ESP32 DevKit power, ESP32-CAM programmer
- **USB-A to USB-C:** Newer ESP32 boards, phone charging
- **Old phone chargers (5V 1A–2A):** Perfect for single ESP32 nodes
- **Old laptop chargers (19V):** Can be buck-converted to 12V

### What to Discard
- Frayed cables (fire hazard)
- Chargers that get hot (internal short risk)
- Non-branded chargers without safety certifications

### Power Distribution Hub
```
Old USB Hub (powered) ──► Multiple 5V nodes
Old Phone Charger ──► Single node
Old Laptop Charger ──► Buck converter ──► 12V rail
```

**Cost Saved:** ₹1,500–₹2,500 (vs. buying new adapters)

---

## 10. Old Mouse/Keyboard → Input Devices

### Use Cases
- **Wired keyboard:** Direct access to hub for troubleshooting (no network needed)
- **Wireless mouse/keyboard:** Control dashboard on TV if connected to hub
- **Old USB numeric keypad:** Physical scene selector (program each key to trigger HA automation)

---

## 11. Old Hard Drives → NAS / Backup Storage

### If Hub is Desktop with SATA
```bash
# Mount old HDD for Frigate recordings and backups
sudo fdisk -l  # Identify drive (e.g., /dev/sdb)
sudo mkfs.ext4 /dev/sdb1
sudo mkdir /mnt/storage
sudo mount /dev/sdb1 /mnt/storage

# Add to /etc/fstab for auto-mount
echo '/dev/sdb1 /mnt/storage ext4 defaults 0 2' | sudo tee -a /etc/fstab

# Use in docker-compose for Frigate
# volumes:
#   - /mnt/storage/frigate:/media/frigate
```

**Cost Saved:** ₹3,000–₹8,000 (vs. buying NAS drive)

---

## 12. Salvage Safety Rules

1. **Always unplug and discharge before opening** any device with capacitors
2. **Never work on mains-connected devices alone** — have someone nearby
3. **Use insulated tools** when working on power supplies
4. **Test with multimeter** before assuming something is "off"
5. **Li-ion cells:** Work on metal tray or concrete floor (fire-safe)
6. **CRT monitors/TVs:** NEVER open — lethal high voltage even when unplugged
7. **Wear safety glasses** when cutting, drilling, or soldering
8. **Ventilate area** when soldering — flux fumes are harmful
9. **Label everything** — "HARVESTED FROM LAPTOP BATTERY — UNTESTED"
10. **When in doubt, throw it out** — a ₹50 component is not worth a hospital visit

---

## 13. What NOT to Reuse

| Item | Why | What to Buy Instead |
|------|-----|---------------------|
| **Mains relays / contactors** | Arcing, welding, fire risk | New certified relays (Songle, Omron) |
| **Gas solenoid valves** | Leak = explosion risk | New certified brass valve |
| **Water inlet valves** | Leak = flooding | New food-grade brass/stainless valve |
| **Smoke sensors (old)** | Sensor degrades, false negatives | New MQ-2 / optical sensor |
| **Fire-rated enclosures** | Must meet safety standards | New ABS V-0 or metal enclosures |
| **GFCI / ELCB** | Life safety device | New certified unit |
| **Fuses** | One-time protection, unknown rating | New correctly-rated fuses |
| **Power cables (frayed)** | Fire and shock hazard | New ISI-marked cables |

---

## Scrap Reuse Summary Table

| Scrap Item | Reuse As | Cost Saved | Difficulty |
|------------|----------|------------|------------|
| Old PC/Laptop | HA Hub | ₹8,000–15,000 | Easy |
| ATX PSU | 5V/12V DC Rail | ₹2,000–3,000 | Medium |
| Old Smartphone | Wall Dashboard | ₹3,000–8,000 | Easy |
| Old Router | WiFi Repeater | ₹1,500–3,000 | Medium |
| Old Speakers | Alert System | ₹1,500–3,000 | Easy |
| Old Webcam | IP Camera | ₹1,500–4,000 | Medium |
| Laptop Battery | 18650 Cells | ₹500–1,500 | Hard |
| USB Cables/Chargers | Power Distribution | ₹1,500–2,500 | Easy |
| Old HDD | NVR Storage | ₹3,000–8,000 | Easy |
| **TOTAL SAVED** | | **₹22,500–48,000** | |

---

*End of 03_Scrap_Reuse_Guide.md*
*Next: 04_Simulation_Guide_Wokwi.md*
