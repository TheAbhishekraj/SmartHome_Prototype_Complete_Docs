# 01_System_Architecture_and_Hub_Setup.md
# SmartHome Prototype — System Architecture & Hub Setup

**Version:** 1.0 | **Date:** August 2026

---

## Table of Contents
1. [Hub Hardware Requirements](#1-hub-hardware-requirements)
2. [Operating System Installation](#2-operating-system-installation)
3. [Docker & Container Stack](#3-docker--container-stack)
4. [Home Assistant Setup](#4-home-assistant-setup)
5. [Mosquitto MQTT Broker](#5-mosquitto-mqtt-broker)
6. [Node-RED Installation](#6-node-red-installation)
7. [Frigate NVR (Camera AI)](#7-frigate-nvr-camera-ai)
8. [Network Architecture](#8-network-architecture)
9. [WiFi Mesh with Old Routers](#9-wifi-mesh-with-old-routers)
10. [IoT VLAN Isolation](#10-iot-vlan-isolation)
11. [Remote Access](#11-remote-access)
12. [Backup Strategy](#12-backup-strategy)
13. [Power Backup / UPS](#13-power-backup--ups)
14. [IP Addressing Scheme](#14-ip-addressing-scheme)

---

## 1. Hub Hardware Requirements

Your old PC or laptop becomes the brain of the entire home. Minimum specs:

| Component | Minimum | Recommended | Notes |
|-----------|---------|-------------|-------|
| **CPU** | Intel i3 / AMD FX | Intel i5 4th gen+ | Frigate AI needs CPU with AVX2 or Coral TPU |
| **RAM** | 4 GB | 8 GB | 4GB works; 8GB comfortable with Frigate |
| **Storage** | 128 GB SSD | 256 GB SSD | SSD mandatory — SD cards/HDD too slow for HA database |
| **Ethernet** | 100 Mbps | 1 Gbps | Wired connection to main router mandatory |
| **USB** | 2 ports | 4 ports | For Coral TPU, Zigbee stick, backup drive |
| **WiFi** | Optional | Optional | Use Ethernet; WiFi only if no cable run |

**Scrap Reuse:** Any PC from 2014+ with 4GB RAM and SSD will work. Old laptops are perfect — built-in UPS (battery).

---

## 2. Operating System Installation

### Option A: Ubuntu Server LTS (Recommended)
```bash
# Download Ubuntu Server 24.04 LTS from ubuntu.com
# Create bootable USB with Rufus (Windows) or Etcher (Linux/Mac)
# Boot from USB, install with defaults

# After first boot, update system
sudo apt update && sudo apt upgrade -y

# Install essential tools
sudo apt install -y curl wget git htop net-tools vim

# Set static IP (edit netplan)
sudo nano /etc/netplan/00-installer-config.yaml
```

**Netplan Config (Static IP):**
```yaml
network:
  version: 2
  ethernets:
    eth0:
      dhcp4: no
      addresses:
        - 192.168.1.10/24
      routes:
        - to: default
          via: 192.168.1.1
      nameservers:
        addresses: [192.168.1.1, 1.1.1.1]
```

```bash
sudo netplan apply
```

### Option B: Home Assistant OS (Direct Install)
If the PC is dedicated (no other use), flash Home Assistant OS directly:
```bash
# Download HAOS image from home-assistant.io/installation/linux
# Use BalenaEtcher to flash to SSD
# Boot and access via http://homeassistant.local:8123
```

**Recommendation:** Use Ubuntu Server + Docker for flexibility (run other services like Frigate, Node-RED, AdGuard).

---

## 3. Docker & Container Stack

```bash
# Install Docker
sudo apt install -y ca-certificates gnupg lsb-release
sudo mkdir -p /etc/apt/keyrings
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg
echo "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
sudo apt update
sudo apt install -y docker-ce docker-ce-cli containerd.io docker-compose-plugin

# Add user to docker group
sudo usermod -aG docker $USER
newgrp docker

# Install Portainer (Web UI for Docker)
docker volume create portainer_data
docker run -d -p 8000:8000 -p 9443:9443 --name portainer   --restart=always -v /var/run/docker.sock:/var/run/docker.sock   -v portainer_data:/data portainer/portainer-ce:latest

# Access Portainer at https://192.168.1.10:9443
```

### Directory Structure on Hub
```
/home/youruser/smarthome/
├── docker-compose.yml
├── homeassistant/
│   └── config/
├── mosquitto/
│   ├── config/
│   ├── data/
│   └── log/
├── nodered/
│   └── data/
├── frigate/
│   └── config/
├── influxdb/
│   └── data/
├── adguard/
│   └── work/
└── backups/
    └── weekly/
```

---

## 4. Home Assistant Setup

### docker-compose.yml
```yaml
version: '3.8'

services:
  homeassistant:
    container_name: homeassistant
    image: ghcr.io/home-assistant/home-assistant:stable
    volumes:
      - ./homeassistant/config:/config
      - /etc/localtime:/etc/localtime:ro
      - /run/dbus:/run/dbus:ro
    restart: unless-stopped
    privileged: true
    network_mode: host
    # USB devices (Zigbee, Coral, etc.)
    devices:
      - /dev/ttyUSB0:/dev/ttyUSB0  # Zigbee coordinator
      # - /dev/bus/usb:/dev/bus/usb  # Coral TPU (if used)

  mosquitto:
    container_name: mosquitto
    image: eclipse-mosquitto:2
    volumes:
      - ./mosquitto/config:/mosquitto/config
      - ./mosquitto/data:/mosquitto/data
      - ./mosquitto/log:/mosquitto/log
    ports:
      - "1883:1883"
      - "9001:9001"
    restart: unless-stopped

  nodered:
    container_name: nodered
    image: nodered/node-red:latest
    volumes:
      - ./nodered/data:/data
    ports:
      - "1880:1880"
    restart: unless-stopped
    environment:
      - TZ=Asia/Kolkata

  frigate:
    container_name: frigate
    image: ghcr.io/blakeblackshear/frigate:stable
    volumes:
      - ./frigate/config:/config:ro
      - /dev/shm:/dev/shm
      - ./frigate/media:/media/frigate
    ports:
      - "5000:5000"
    environment:
      - FRIGATE_RTSP_PASSWORD=your_secure_password
    privileged: true
    # For Coral TPU:
    # devices:
    #   - /dev/bus/usb:/dev/bus/usb

  influxdb:
    container_name: influxdb
    image: influxdb:2.7
    volumes:
      - ./influxdb/data:/var/lib/influxdb2
    ports:
      - "8086:8086"
    environment:
      - DOCKER_INFLUXDB_INIT_MODE=setup
      - DOCKER_INFLUXDB_INIT_USERNAME=admin
      - DOCKER_INFLUXDB_INIT_PASSWORD=your_influx_password
      - DOCKER_INFLUXDB_INIT_ORG=smarthome
      - DOCKER_INFLUXDB_INIT_BUCKET=home_metrics
    restart: unless-stopped

  adguardhome:
    container_name: adguardhome
    image: adguard/adguardhome:latest
    volumes:
      - ./adguard/work:/opt/adguardhome/work
      - ./adguard/conf:/opt/adguardhome/conf
    ports:
      - "53:53/tcp"
      - "53:53/udp"
      - "3000:3000"
    restart: unless-stopped
```

### Start Everything
```bash
cd /home/youruser/smarthome
docker compose up -d

# Check status
docker compose ps

# View Home Assistant logs
docker logs -f homeassistant
```

### First-Time HA Setup
1. Open `http://192.168.1.10:8123`
2. Create owner account
3. Set location (for sun automation)
4. Skip initial device discovery (we'll add manually)
5. Install HACS (Home Assistant Community Store):
   ```bash
   # In Portainer, open homeassistant container console
   wget -O - https://get.hacs.xyz | bash -
   # Restart HA container
   ```
6. Install essential integrations: MQTT, ESPHome, Node-RED Companion, Frigate, Sun

---

## 5. Mosquitto MQTT Broker

### mosquitto/config/mosquitto.conf
```
persistence true
persistence_location /mosquitto/data/
log_dest file /mosquitto/log/mosquitto.log

listener 1883
allow_anonymous true

# For production (recommended):
# password_file /mosquitto/config/passwd
# allow_anonymous false
# listener 1883
```

### Test MQTT
```bash
# Install mosquitto clients
sudo apt install -y mosquitto-clients

# Subscribe to all topics
mosquitto_sub -h 192.168.1.10 -t "#" -v

# Publish test message
mosquitto_pub -h 192.168.1.10 -t "test/hello" -m "MQTT is working!"
```

### Home Assistant MQTT Integration
1. Settings → Devices & Services → Add Integration → MQTT
2. Broker: `192.168.1.10`, Port: `1883`
3. Submit → Done
4. ESPHome devices will auto-discover via MQTT + API

---

## 6. Node-RED Installation

Already in docker-compose. Access at `http://192.168.1.10:1880`

### Essential Node-RED Nodes
Install via Menu → Manage Palette → Install:
- `node-red-contrib-home-assistant-websocket`
- `node-red-dashboard`
- `node-red-node-email`
- `node-red-node-telegrambot`

### Node-RED → Home Assistant Connection
1. Install "Node-RED Companion" integration in HA (via HACS)
2. In Node-RED, add HA Server config:
   - Base URL: `http://192.168.1.10:8123`
   - Access Token: Create in HA → Profile → Long-Lived Access Tokens

---

## 7. Frigate NVR (Camera AI)

### frigate/config/config.yml
```yaml
mqtt:
  host: 192.168.1.10
  port: 1883

detectors:
  cpu:
    type: cpu
    num_threads: 4
    # Replace with coral for better performance:
    # coral:
    #   type: edgetpu
    #   device: usb

cameras:
  front_door_cam:
    ffmpeg:
      inputs:
        - path: rtsp://192.168.1.101:8554/mjpeg/1
          roles:
            - detect
            - record
    detect:
      width: 640
      height: 480
      fps: 5
    record:
      enabled: true
      retain:
        days: 7
      events:
        retain:
          default: 14
    snapshots:
      enabled: true
    motion:
      mask:
        - 640,0,640,100,0,100,0,0  # Mask sky if needed

detect:
  enabled: true
  max_disappeared: 25

objects:
  track:
    - person
    - car
    - cat
    - dog

# Optional: Enable audio detection for glass break
audio:
  enabled: false
  listen:
    - scream
    - glass_breaking
```

---

## 8. Network Architecture

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                           INTERNET MODEM / ONT                              │
│                              192.168.1.1                                    │
└─────────────────────────────────────────────────────────────────────────────┘
                                      │
                                      ▼
┌─────────────────────────────────────────────────────────────────────────────┐
│                         MAIN ROUTER (OpenWRT)                               │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐         │
│  │   LAN Port  │  │   LAN Port  │  │   LAN Port  │  │   LAN Port  │         │
│  │  192.168.1.2│  │  192.168.1.3│  │  192.168.1.4│  │  192.168.1.5│         │
│  └─────────────┘  └─────────────┘  └─────────────┘  └─────────────┘         │
│       │                │                │                │                    │
│       ▼                ▼                ▼                ▼                    │
│  ┌─────────┐     ┌─────────┐     ┌─────────┐     ┌─────────┐                │
│  │  HUB    │     │ Old Rtr │     │ Old Rtr │     │  PC/    │                │
│  │  HA PC  │     │Repeater │     │Repeater │     │ Laptop  │                │
│  │.1.10    │     │.1.20    │     │.1.30    │     │ (User)  │                │
│  └─────────┘     └────┬────┘     └────┬────┘     └─────────┘                │
│                       │               │                                       │
│                  WiFi: IoT_2.4G   WiFi: IoT_2.4G                            │
│                  (Ground Floor)   (First Floor)                               │
└─────────────────────────────────────────────────────────────────────────────┘
```

---

## 9. WiFi Mesh with Old Routers

### Flash Old Router with OpenWRT
1. Check compatibility: `openwrt.org/toh/start`
2. Download factory image for your router model
3. Flash via router's stock firmware upgrade page
4. Configure as "Dumb AP / Repeater":

```bash
# SSH into OpenWRT router
ssh root@192.168.1.20

# Set static IP
uci set network.lan.ipaddr='192.168.1.20'
uci set network.lan.gateway='192.168.1.1'
uci set network.lan.dns='192.168.1.1'
uci delete network.lan.type  # Remove bridge if exists
uci commit network

# Disable DHCP (main router handles it)
uci set dhcp.lan.ignore='1'
uci commit dhcp

# Configure WiFi
uci set wireless.radio0.disabled='0'
uci set wireless.@wifi-iface[0].ssid='SmartHome_IoT'
uci set wireless.@wifi-iface[0].encryption='psk2'
uci set wireless.@wifi-iface[0].key='YourStrongPassword123'
uci set wireless.@wifi-iface[0].mode='ap'
uci set wireless.radio0.channel='6'  # Different from main router
uci commit wireless

# Enable and restart
wifi up
/etc/init.d/network restart
/etc/init.d/dnsmasq restart
```

### WiFi Tips for IoT
- **Use 2.4GHz only** for ESP32 nodes (better range, wall penetration)
- **Separate SSID** for IoT devices: `SmartHome_IoT`
- **Same password** across all APs for seamless roaming
- **Channel planning:** Main router CH1, Repeater 1 CH6, Repeater 2 CH11
- **Transmit power:** Reduce to 17-20 dBm to reduce interference

---

## 10. IoT VLAN Isolation

If your main router supports VLANs (OpenWRT, TP-Link Omada, etc.):

```
VLAN 10: Management (Hub, your PC, admin devices) → 192.168.10.0/24
VLAN 20: IoT Devices (ESP32 nodes, cameras, sensors) → 192.168.20.0/24
VLAN 30: Family Devices (Phones, laptops, tablets) → 192.168.30.0/24
VLAN 40: Guest → 192.168.40.0/24
```

**Firewall Rules:**
- IoT (VLAN 20) can ONLY talk to Hub (VLAN 10) on ports 1883, 6053, 8123
- IoT CANNOT access internet or family devices
- Family devices CAN talk to IoT (for dashboard access)
- Guest CANNOT talk to anyone

**Why:** If an ESP32 is compromised, it cannot attack your laptop or browse the internet.

---

## 11. Remote Access

### Option A: Tailscale (Recommended — Easiest)
```bash
# Install on Hub
curl -fsSL https://tailscale.com/install.sh | sh
sudo tailscale up

# Install on your phone (App Store / Play Store)
# Login with same account
# Access HA at: http://hub-pc:8123 (magic DNS)
```

**Pros:** Zero config, encrypted, peer-to-peer, free for personal use  
**Cons:** Needs Tailscale app on each device

### Option B: Cloudflare Tunnel
```bash
# Install cloudflared
curl -L --output cloudflared.deb https://github.com/cloudflare/cloudflared/releases/latest/download/cloudflared-linux-amd64.deb
sudo dpkg -i cloudflared.deb

# Authenticate
cloudflared tunnel login

# Create tunnel
cloudflared tunnel create smarthome

# Config at ~/.cloudflared/config.yml
tunnel: YOUR_TUNNEL_ID
credentials-file: /home/youruser/.cloudflared/YOUR_TUNNEL_ID.json

ingress:
  - hostname: ha.yourdomain.com
    service: http://localhost:8123
  - hostname: nodered.yourdomain.com
    service: http://localhost:1880
  - service: http_status:404

# Route DNS
cloudflared tunnel route dns smarthome ha.yourdomain.com

# Run
cloudflared tunnel run smarthome
```

**Pros:** Custom domain, no client app needed, DDoS protection  
**Cons:** Slightly more complex setup, traffic routes through Cloudflare

### Option C: Both (Best)
- Tailscale for admin access (full network)
- Cloudflare for family dashboard access (web only)

---

## 12. Backup Strategy

### Automated Weekly Backup Script
```bash
#!/bin/bash
# /home/youruser/smarthome/backup.sh

BACKUP_DIR="/home/youruser/smarthome/backups/weekly"
DATE=$(date +%Y%m%d_%H%M%S)
mkdir -p $BACKUP_DIR

# Backup Home Assistant
tar czf $BACKUP_DIR/ha_config_$DATE.tar.gz ./homeassistant/config

# Backup Node-RED
tar czf $BACKUP_DIR/nodered_data_$DATE.tar.gz ./nodered/data

# Backup Mosquitto
tar czf $BACKUP_DIR/mosquitto_$DATE.tar.gz ./mosquitto

# Backup Frigate config
tar czf $BACKUP_DIR/frigate_config_$DATE.tar.gz ./frigate/config

# Keep only last 10 backups
ls -t $BACKUP_DIR/*.tar.gz | tail -n +11 | xargs -r rm

# OFF-BOX ROTATION: Sync backups to an external USB mount, NAS, or Cloud
# E.g., copy to a mounted NAS share:
# cp $BACKUP_DIR/*_$DATE.tar.gz /mnt/external_nas/backups/
```

```bash
# Make executable and add to crontab
chmod +x /home/youruser/smarthome/backup.sh
crontab -e
# Add: 0 2 * * 0 /home/youruser/smarthome/backup.sh
```

### Off-Box & Cloud Storage Integration (CRITICAL)
Local backups are worthless if the host SSD fails. Implement an automated off-box pushing mechanism:
1. **Google Drive Sync (via Home Assistant Add-on):**
   - If running HAOS or Supervised, configure the **Home Assistant Google Drive Backup** addon from HACS/Github (`snabba/home-assistant-google-drive-backup`).
   - Link your Google account and set a retention policy (e.g., keep 4 backups locally, 10 in the cloud).
2. **Generic Docker Off-Site Sync (via `rclone`):**
   - Install rclone: `sudo apt install rclone`
   - Configure a remote target (Google Drive, OneDrive, AWS S3, or Backblaze B2): `rclone config`
   - Append this sync line to the bottom of the `/home/youruser/smarthome/backup.sh` script:
     ```bash
     # Upload new configs to cloud remote 'gdrive' under the 'smarthome_backups' folder
     rclone sync /home/youruser/smarthome/backups gdrive:smarthome_backups --verbose
     ```

### Restore Verification Test (Mandatory Semi-Annual Audit)
A backup is only as good as its restore. Once every 6 months, verify the restore path:
- **Clean Environment Test:** Spin up a temporary Docker environment on a secondary PC or laptop.
- **Copy & Extract:** Copy the backup files onto the test machine and extract them matching the identical folder tree structure:
  ```bash
  tar -xzf ha_config_[datetime].tar.gz -C ./homeassistant/config --strip-components=1
  ```
- **Execution Run:** Spin up the stack: `docker compose up -d`
- **Pass Criteria:** Verify you can log in, all major entities match, dashboards load, Node-RED flows are visible, and historical databases load without corruption warnings in logs.

---

## 13. Power Backup / UPS

### For the Hub (Old PC/Laptop)
- **If laptop:** Built-in battery = 2–4 hours UPS. Keep charger plugged in.
- **If desktop:** Use APC/Microtek 600VA UPS (~₹2,500). Provides 15–30 minutes.
- **Critical:** Hub must stay online during outages for safety monitoring.

### For Network (Router + Repeaters)
- **Old router on UPS:** Use same UPS as hub or separate 12V UPS module.
- **DIY Router UPS:** 12V 7Ah battery + 12V charger + diode ORV (~₹800).

### ATX PSU Minimum Load Note
- **ATX Regulation:** If repurposing an old ATX desktop PSU for central 12V/5V distribution, you **MUST** install a minimum load (dummy load) resistor. Desktop ATX power supplies regulate output voltage by sensing the load on the 5V and/or 3.3V rails. If the 5V rail is unloaded while the 12V rail runs heavy loads (pumps, curtains), the 12V output will sag (below 10.5V) or the PSU will trip into safety shutdown.
- **Solution:** Place a high-wattage power resistor (10Ω, 10-25W aluminum-clad resistor) between a red wire (+5V) and black wire (GND). Mount it to a metal chassis; it will generate heat. This stabilizes the 12V output for reliable stepper motor, contactor, and solenoid actuator performance.

### For Critical ESP32 Nodes
Nodes that MUST work during power cut:
- Gas leak detector
- Fire/smoke detectors
- Security sensors
- Panic button

**Power Options:**
| Method | Cost | Duration | Best For |
|--------|------|----------|----------|
| USB Power Bank (10,000mAh) | ₹800 | 8–12 hours | Single ESP32 |
| 18650 Battery + TP4056 + MT3608 | ₹250 | 6–10 hours | Custom node |
| 12V 7Ah Battery + 5V Buck | ₹600 | 24+ hours | Multiple nodes |
| Supercapacitor (10F) | ₹150 | 30–60 sec | Graceful shutdown only |

**Recommended:** Each safety-critical node gets a small 18650 battery holder + charging module + 5V boost. Total ₹250 per node.

---

## 14. IP Addressing Scheme

| Device | IP Address | Purpose |
|--------|-----------|---------|
| Main Router | 192.168.1.1 | Gateway, DHCP |
| OpenWRT AP 1 | 192.168.1.20 | Ground Floor WiFi |
| OpenWRT AP 2 | 192.168.1.30 | First Floor WiFi |
| Home Assistant Hub | 192.168.1.10 | Core automation |
| AdGuard DNS | 192.168.1.10:53 | DNS filtering |
| Node-RED | 192.168.1.10:1880 | Automation logic |
| Frigate | 192.168.1.10:5000 | Camera NVR |
| InfluxDB | 192.168.1.10:8086 | Metrics storage |
| Portainer | 192.168.1.10:9443 | Docker management |
| ESP32 Nodes | 192.168.1.100–199 | DHCP reserved by MAC |
| Cameras | 192.168.1.200–210 | Static IP |

### DHCP Reservations
In main router, reserve IPs by MAC address for all ESP32 nodes. This ensures:
- Frigate always finds cameras at same IP
- Node-RED flows don't break on IP change
- Easier troubleshooting

---

## Quick Start Checklist

- [ ] Old PC/laptop identified and tested
- [ ] Ubuntu Server installed, static IP set
- [ ] Docker + Docker Compose installed
- [ ] docker-compose.yml created, all containers running
- [ ] Home Assistant accessible at http://192.168.1.10:8123
- [ ] MQTT broker tested with mosquitto_pub/sub
- [ ] Node-RED connected to Home Assistant
- [ ] Old router flashed with OpenWRT, configured as repeater
- [ ] WiFi coverage verified on both floors (>-65 dBm)
- [ ] Tailscale or Cloudflare Tunnel configured for remote access
- [ ] Backup script created and scheduled
- [ ] UPS connected to hub and main router

---

*End of 01_System_Architecture_and_Hub_Setup.md*
*Next: 02_Node_Clubbing_BOM_and_Cost.md*
