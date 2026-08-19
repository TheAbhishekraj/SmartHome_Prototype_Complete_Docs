# 07_Home_Assistant_Configuration_and_Dashboard.md
# SmartHome Prototype — Home Assistant Setup & Lovelace Dashboard

**Version:** 1.0 | **Date:** August 2026

---

## Table of Contents
1. [Initial HA Setup](#1-initial-ha-setup)
2. [Core Integrations](#2-core-integrations)
3. [Lovelace Dashboard YAML](#3-lovelace-dashboard-yaml)
4. [Mobile App Setup](#4-mobile-app-setup)
5. [Notifications (Mobile Alerts)](#5-notifications-mobile-alerts)
6. [Entity Organization](#6-entity-organization)
7. [Automations (Basic HA)](#7-automations-basic-ha)
8. [Backup & Restore](#8-backup--restore)

---

## 1. Initial HA Setup

After first boot at `http://192.168.1.10:8123`:

### Step 1: Create Owner Account
- Name: Your Name
- Username: admin
- Password: Strong unique password

### Step 2: Location
- Set your home address (for sun automation, weather)
- Elevation: Your city's elevation in meters
- Time Zone: Asia/Kolkata

### Step 3: Install HACS
```bash
# In Portainer, open homeassistant container console
wget -O - https://get.hacs.xyz | bash -
# Restart HA container
```

### Step 4: Install Essential Integrations
Settings → Devices & Services → Add Integration:
- **MQTT** → Broker: 192.168.1.10, Port: 1883
- **ESPHome** → Devices auto-discover
- **Sun** → Auto-detected
- **Mobile App** → For phone notifications
- **Node-RED Companion** → Via HACS

### Step 5: Create Areas
Settings → Areas & Zones → Create:
- Garden / Balcony
- Kitchen
- Living Room
- Master Bedroom
- Second Bedroom
- Master Bathroom
- Common Bathroom
- Water / Pump
- Security
- Aquarium

Assign each ESPHome device to its area.

---

## 2. Core Integrations

### MQTT Configuration
```yaml
# configuration.yaml (or UI: Settings → Devices → MQTT)
mqtt:
  broker: 192.168.1.10
  port: 1883
  discovery: true
  discovery_prefix: homeassistant
```

### Recorder (Database)
```yaml
# configuration.yaml
recorder:
  db_url: sqlite:////config/home-assistant_v2.db
  purge_keep_days: 30
  exclude:
    domains:
      - updater
      - weblink
```

### InfluxDB (Long-term metrics)
```yaml
# configuration.yaml
influxdb:
  host: 192.168.1.10
  port: 8086
  database: home_metrics
  username: admin
  password: !secret influx_password
  max_retries: 3
  default_measurement: state
  include:
    domains:
      - sensor
      - binary_sensor
      - switch
```

---

## 3. Lovelace Dashboard YAML

### Main Dashboard (`ui-lovelace.yaml`)

```yaml
title: SmartHome Dashboard
views:
  # ═══════════════════════════════════════════════
  # VIEW 1: OVERVIEW
  # ═══════════════════════════════════════════════
  - title: Overview
    path: overview
    icon: mdi:home
    cards:
      - type: entities
        title: 🏠 System Status
        entities:
          - entity: sensor.mains_voltage
            name: Mains Voltage
          - entity: sensor.mains_current
            name: Mains Current
          - entity: sensor.mains_power
            name: Total Power
          - entity: sensor.mains_energy
            name: Total Energy
          - entity: binary_sensor.gas_leak_alert
            name: Gas Status
          - entity: binary_sensor.smoke_alert
            name: Smoke Status
          - entity: binary_sensor.kitchen_water_leak
            name: Water Leak

      - type: glance
        title: 🔒 Security
        entities:
          - entity: binary_sensor.front_door
            name: Front Door
          - entity: binary_sensor.back_door
            name: Back Door
          - entity: binary_sensor.lr_window
            name: LR Window
          - entity: binary_sensor.bed_window
            name: Bed Window
          - entity: switch.alarm_armed
            name: Alarm
          - entity: switch.alarm_siren
            name: Siren

      - type: weather-forecast
        entity: weather.home

      - type: button
        name: 🚨 PANIC
        tap_action:
          action: call-service
          service: script.panic_alert
        icon: mdi:alarm-light
        icon_height: 64px
        card_mod:
          style: |
            ha-card {
              background-color: #ff4444;
              color: white;
            }

  # ═══════════════════════════════════════════════
  # VIEW 2: CLIMATE & COMFORT
  # ═══════════════════════════════════════════════
  - title: Climate
    path: climate
    icon: mdi:thermometer
    cards:
      - type: entities
        title: 🌡️ Temperatures
        entities:
          - sensor.kitchen_temperature
          - sensor.living_room_temperature
          - sensor.bedroom_temperature
          - sensor.bathroom_temperature
          - sensor.aquarium_temperature
          - sensor.geyser_temperature

      - type: entities
        title: 💧 Humidity
        entities:
          - sensor.kitchen_humidity
          - sensor.living_room_humidity
          - sensor.bedroom_humidity
          - sensor.bathroom_humidity

      - type: thermostat
        entity: climate.living_room_ac
        name: Living Room AC

      - type: entities
        title: 🌬️ Air Quality
        entities:
          - sensor.pm2_5
          - sensor.co2
          - sensor.tvoc
          - switch.ventilation

  # ═══════════════════════════════════════════════
  # VIEW 3: LIGHTING
  # ═══════════════════════════════════════════════
  - title: Lights
    path: lights
    icon: mdi:lightbulb
    cards:
      - type: grid
        columns: 2
        cards:
          - type: light
            entity: switch.garden_light
            name: Garden
          - type: light
            entity: switch.kitchen_light
            name: Kitchen
          - type: light
            entity: switch.living_room_light
            name: Living Room
          - type: light
            entity: switch.bedroom_light
            name: Bedroom
          - type: light
            entity: switch.bathroom_light
            name: Bathroom
          - type: light
            entity: switch.aquarium_light
            name: Aquarium

      - type: entities
        title: 🌅 Curtains
        entities:
          - entity: cover.living_room_curtain
            name: Living Room

  # ═══════════════════════════════════════════════
  # VIEW 4: WATER & PUMP
  # ═══════════════════════════════════════════════
  - title: Water
    path: water
    icon: mdi:water
    cards:
      - type: gauge
        entity: sensor.oh_tank_level_ultrasonic
        name: Overhead Tank
        min: 0
        max: 100
        severity:
          green: 60
          yellow: 30
          red: 10

      - type: entities
        title: 💧 Tank Status
        entities:
          - binary_sensor.oh_tank_empty
          - binary_sensor.oh_tank_mid
          - binary_sensor.oh_tank_full
          - binary_sensor.sump_low
          - binary_sensor.sump_full

      - type: entities
        title: 🔧 Pump Control
        entities:
          - switch.main_water_pump
          - switch.pressure_pump
          - sensor.pump_current

      - type: history-graph
        title: Tank Level History
        entities:
          - sensor.oh_tank_level_ultrasonic
        hours_to_show: 24
        refresh_interval: 60

  # ═══════════════════════════════════════════════
  # VIEW 5: GARDEN
  # ═══════════════════════════════════════════════
  - title: Garden
    path: garden
    icon: mdi:flower
    cards:
      - type: entities
        title: 🌱 Soil Moisture
        entities:
          - sensor.soil_moisture_a
          - sensor.soil_moisture_b
          - sensor.soil_moisture_c

      - type: entities
        title: 🌧️ Weather
        entities:
          - binary_sensor.rain_detected
          - sensor.garden_light_level
          - binary_sensor.garden_motion

      - type: entities
        title: 💦 Watering
        entities:
          - switch.water_valve_a
          - switch.water_valve_b
          - switch.water_valve_c
          - fan.awning_motor

  # ═══════════════════════════════════════════════
  # VIEW 6: SECURITY CAMERAS
  # ═══════════════════════════════════════════════
  - title: Cameras
    path: cameras
    icon: mdi:cctv
    cards:
      - type: picture-entity
        entity: camera.night_security_camera
        camera_view: live
        show_name: true
        show_state: false

      - type: picture-entity
        entity: camera.video_doorbell
        camera_view: live
        show_name: true
        show_state: false

      - type: entities
        title: 🔔 Doorbell
        entities:
          - binary_sensor.doorbell_button
          - switch.door_strike  # If installed

  # ═══════════════════════════════════════════════
  # VIEW 7: AQUARIUM
  # ═══════════════════════════════════════════════
  - title: Aquarium
    path: aquarium
    icon: mdi:fish
    cards:
      - type: gauge
        entity: sensor.aquarium_temperature
        name: Water Temp
        min: 20
        max: 35
        severity:
          green: 24
          yellow: 27
          red: 30

      - type: entities
        title: 🐟 Controls
        entities:
          - switch.aquarium_heater
          - switch.aquarium_light
          - switch.filter_pump
          - switch.top_up_pump
          - sensor.water_tds

      - type: button
        name: 🍽️ Feed Fish
        tap_action:
          action: call-service
          service: button.press
          target:
            entity_id: button.fish_feeder
        icon: mdi:fish-food

  # ═══════════════════════════════════════════════
  # VIEW 8: SCENES
  # ═══════════════════════════════════════════════
  - title: Scenes
    path: scenes
    icon: mdi:palette
    cards:
      - type: grid
        columns: 2
        cards:
          - type: button
            name: 🌅 Morning
            tap_action:
              action: call-service
              service: scene.turn_on
              target:
                entity_id: scene.morning
            icon: mdi:weather-sunset-up
          - type: button
            name: 🌙 Night
            tap_action:
              action: call-service
              service: scene.turn_on
              target:
                entity_id: scene.night
            icon: mdi:weather-night
          - type: button
            name: 🚪 Away
            tap_action:
              action: call-service
              service: scene.turn_on
              target:
                entity_id: scene.away
            icon: mdi:shield-home
          - type: button
            name: 🎉 Party
            tap_action:
              action: call-service
              service: scene.turn_on
              target:
                entity_id: scene.party
            icon: mdi:party-popper
          - type: button
            name: 🎬 Movie
            tap_action:
              action: call-service
              service: scene.turn_on
              target:
                entity_id: scene.movie
            icon: mdi:movie-open
          - type: button
            name: 🚨 Emergency
            tap_action:
              action: call-service
              service: script.emergency_mode
            icon: mdi:alert-octagon
            card_mod:
              style: |
                ha-card {
                  background-color: #ff4444;
                  color: white;
                }
```

### Scenes Configuration (`scenes.yaml`)
```yaml
- name: Morning
  entities:
    switch.bedroom_light: on
    cover.living_room_curtain: open
    switch.geyser_power: on
    switch.kitchen_light: on
    switch.alarm_armed: off

- name: Night
  entities:
    switch.garden_light: off
    switch.living_room_light: off
    switch.bedroom_light: off
    switch.bathroom_light: off
    cover.living_room_curtain: closed
    switch.geyser_power: off
    switch.alarm_armed: on
    switch.aquarium_light: off

- name: Away
  entities:
    switch.garden_light: off
    switch.kitchen_light: off
    switch.living_room_light: off
    switch.bedroom_light: off
    switch.bathroom_light: off
    switch.geyser_power: off
    switch.aquarium_light: off
    switch.alarm_armed: on
    cover.living_room_curtain: closed

- name: Party
  entities:
    switch.living_room_light: on
    switch.garden_light: on
    switch.alarm_armed: off
    cover.living_room_curtain: open

- name: Movie
  entities:
    switch.living_room_light: off
    cover.living_room_curtain: closed
    switch.alarm_armed: off
```

---

## 4. Mobile App Setup

### Install
- Android: Play Store → "Home Assistant"
- iOS: App Store → "Home Assistant"

### Connect
1. On same WiFi as hub
2. App auto-discovers: `http://192.168.1.10:8123`
3. Log in with your HA account
4. Enable notifications: App Settings → Notifications → Enable

### Enable Sensors on Phone
App Configuration → Manage Sensors → Enable:
- Battery Level
- WiFi Connection
- Geocoded Location (for away/home detection)
- Light Sensor (optional)

### Add to Dashboard
The mobile app automatically shows your Lovelace dashboard. You can also create a mobile-specific view.

---

## 5. Notifications (Mobile Alerts)

### Basic Alert Script (`scripts.yaml`)
```yaml
panic_alert:
  alias: "🚨 PANIC ALERT"
  sequence:
    - service: notify.mobile_app_your_phone
      data:
        title: "🚨 PANIC BUTTON PRESSED"
        message: "Panic button activated at {{ now().strftime('%H:%M') }}"
        data:
          priority: high
          ttl: 0
          vibrationPattern: "100, 1000, 100, 1000, 100"
    - service: switch.turn_on
      target:
        entity_id: switch.alarm_siren
    - delay: "00:05:00"
    - service: switch.turn_off
      target:
        entity_id: switch.alarm_siren

gas_leak_alert:
  alias: "⚠️ Gas Leak Alert"
  sequence:
    - service: notify.mobile_app_your_phone
      data:
        title: "⚠️ GAS LEAK DETECTED"
        message: "Kitchen gas sensor reading: {{ states('sensor.kitchen_gas_level') }} ppm"
        data:
          priority: high
          ttl: 0

smoke_alert:
  alias: "🔥 Smoke Detected"
  sequence:
    - service: notify.mobile_app_your_phone
      data:
        title: "🔥 SMOKE DETECTED"
        message: "Location: {{ trigger.event.data.location | default('Unknown') }}"
        data:
          priority: high
          ttl: 0

water_leak_alert:
  alias: "💧 Water Leak Alert"
  sequence:
    - service: notify.mobile_app_your_phone
      data:
        title: "💧 WATER LEAK"
        message: "Leak detected in {{ trigger.event.data.location | default('Unknown') }}"
        data:
          priority: high

emergency_mode:
  alias: "🚨 Emergency Mode"
  sequence:
    - service: switch.turn_on
      target:
        entity_id:
          - switch.kitchen_light
          - switch.living_room_light
          - switch.bedroom_light
          - switch.bathroom_light
          - switch.garden_light
    - service: switch.turn_off
      target:
        entity_id:
          - switch.alarm_siren
          - switch.alarm_armed
    - service: notify.mobile_app_your_phone
      data:
        title: "🚨 Emergency Mode Activated"
        message: "All lights ON. Alarm disarmed."
```

### Automation to Trigger Alerts (`automations.yaml`)
```yaml
- alias: "Gas Leak → Alert"
  trigger:
    - platform: event
      event_type: esphome.gas_leak
  action:
    - service: script.gas_leak_alert

- alias: "Smoke Detected → Alert"
  trigger:
    - platform: event
      event_type: esphome.smoke_detected
  action:
    - service: script.smoke_alert

- alias: "Water Leak → Alert"
  trigger:
    - platform: event
      event_type: esphome.water_leak
  action:
    - service: script.water_leak_alert

- alias: "Panic Button → Alert"
  trigger:
    - platform: event
      event_type: esphome.panic_pressed
  action:
    - service: script.panic_alert

- alias: "Dry Run → Alert"
  trigger:
    - platform: event
      event_type: esphome.dry_run_alert
  action:
    - service: notify.mobile_app_your_phone
      data:
        title: "⚠️ Pump Dry Run"
        message: "Pump dry run detected. Pump stopped automatically."

- alias: "Fall Detection → Alert"
  trigger:
    - platform: event
      event_type: esphome.no_movement_alert
  action:
    - service: notify.mobile_app_your_phone
      data:
        title: "🚨 Fall Detection"
        message: "No movement detected in {{ trigger.event.data.location }} for 30 minutes"

- alias: "Door Left Open → Alert"
  trigger:
    - platform: state
      entity_id:
        - binary_sensor.front_door
        - binary_sensor.lr_window
        - binary_sensor.bed_window
      to: "on"
      for: "00:05:00"    # Alert after 5 minutes
  condition:
    - condition: state
      entity_id: sun.sun
      state: "below_horizon"
  action:
    - service: notify.mobile_app_your_phone
      data:
        title: "🚪 Door/Window Open"
        message: "{{ trigger.to_state.attributes.friendly_name }} has been open for 5 minutes at night"
```

---

## 6. Entity Organization

### Custom Groups (`groups.yaml`)
```yaml
all_lights:
  name: All Lights
  entities:
    - switch.garden_light
    - switch.kitchen_light
    - switch.living_room_light
    - switch.bedroom_light
    - switch.bathroom_light
    - switch.aquarium_light

all_doors:
  name: All Doors
  entities:
    - binary_sensor.front_door
    - binary_sensor.back_door

all_windows:
  name: All Windows
  entities:
    - binary_sensor.lr_window
    - binary_sensor.bed_window

safety_sensors:
  name: Safety Sensors
  entities:
    - binary_sensor.gas_leak_alert
    - binary_sensor.smoke_alert
    - binary_sensor.kitchen_water_leak
    - binary_sensor.bathroom_water_leak
    - binary_sensor.fire_detected_gf
```

---

## 7. Automations (Basic HA)

### Morning Routine
```yaml
- alias: "Morning Routine"
  trigger:
    - platform: time
      at: "07:00:00"
  condition:
    - condition: time
      weekday:
        - mon
        - tue
        - wed
        - thu
        - fri
  action:
    - service: scene.turn_on
      target:
        entity_id: scene.morning
    - service: cover.open_cover
      target:
        entity_id: cover.living_room_curtain
    - service: switch.turn_on
      target:
        entity_id: switch.geyser_power
    - delay: "00:30:00"
    - service: switch.turn_off
      target:
        entity_id: switch.geyser_power
```

### Night Routine
```yaml
- alias: "Night Routine"
  trigger:
    - platform: time
      at: "22:30:00"
  action:
    - service: scene.turn_on
      target:
        entity_id: scene.night
    - service: switch.turn_off
      target:
        entity_id: switch.geyser_power
```

### Auto-Away Mode
```yaml
- alias: "Auto Away Mode"
  trigger:
    - platform: state
      entity_id: person.your_name
      to: "not_home"
      for: "00:15:00"
  action:
    - service: scene.turn_on
      target:
        entity_id: scene.away
    - service: notify.mobile_app_your_phone
      data:
        title: "🏠 Away Mode"
        message: "Nobody home. Security armed."
```

### Auto-Home Mode
```yaml
- alias: "Auto Home Mode"
  trigger:
    - platform: state
      entity_id: person.your_name
      to: "home"
  action:
    - service: switch.turn_off
      target:
        entity_id: switch.alarm_armed
    - service: notify.mobile_app_your_phone
      data:
        title: "🏠 Welcome Home"
        message: "Alarm disarmed. Lights on."
```

---

## 8. Backup & Restore

### Automated Backup
```yaml
# configuration.yaml
homeassistant:
  packages: !include_dir_named packages

# Enable backup integration (built-in)
# Settings → System → Backups → Create Backup
```

### Weekly Automated Backup Script
See File 01, Section 12 for the bash script.

### What to Backup
1. Home Assistant config folder (`/config`)
2. Node-RED flows (`/data`)
3. Mosquitto config (`/mosquitto`)
4. Frigate config (`/frigate`)
5. InfluxDB data (`/influxdb`)

### Restore Process
1. Fresh install Docker + containers
2. Copy backup files to correct locations
3. Start containers
4. Verify all entities appear
5. Test critical automations

---

*End of 07_Home_Assistant_Configuration_and_Dashboard.md*
*Next: 08_Node_RED_Automations.md*
