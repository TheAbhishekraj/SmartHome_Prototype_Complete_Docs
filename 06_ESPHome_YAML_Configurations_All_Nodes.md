# 06_ESPHome_YAML_Configurations_All_Nodes.md
# SmartHome Prototype — Complete ESPHome YAML Library

**Version:** 1.0 | **Date:** August 2026

---

## Table of Contents
1. [YAML Basics & Tuning](#1-yaml-basics--tuning)
2. [NODE-A1: Garden Controller](#2-node-a1-garden-controller)
3. [NODE-B1: Kitchen Safety (CRITICAL)](#3-node-b1-kitchen-safety-critical)
4. [NODE-C1: Water Tank & Pump](#4-node-c1-water-tank--pump)
5. [NODE-D1: Living Room Comfort](#5-node-d1-living-room-comfort)
6. [NODE-E1: Master Bathroom](#6-node-e1-master-bathroom)
7. [NODE-F1: Night Security Camera](#7-node-f1-night-security-camera)
8. [NODE-F3: Intrusion Alarm](#8-node-f3-intrusion-alarm)
9. [NODE-G2: Air Quality](#9-node-g2-air-quality)
10. [NODE-H1: Aquarium](#10-node-h1-aquarium)
11. [NODE-S1: Electrical Monitor](#11-node-s1-electrical-monitor)
12. [NODE-S3: Panic Button](#12-node-s3-panic-button)
13. [NODE-S5: Fire Detection](#13-node-s5-fire-detection)
14. [secrets.yaml Template](#14-secretsyaml-template)
15. [OTA & Troubleshooting](#15-ota--troubleshooting)

---

## 1. YAML Basics & Tuning

### Common Header (Use for ALL nodes)
```yaml
esphome:
  name: node-name          # lowercase_underscore
  friendly_name: "Human Name"

esp32:
  board: esp32dev
  framework:
    type: arduino

# OR for ESP8266:
# esp8266:
#   board: nodemcuv2

logger:

api:
  encryption:
    key: !secret api_key

ota:
  - platform: esphome
    password: !secret ota_password

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password
  ap:
    ssid: "Node Fallback"
    password: !secret wifi_password

captive_portal:
```

### secrets.yaml
```yaml
wifi_ssid: "SmartHome_IoT"
wifi_password: "YourStrongWiFiPassword"
api_key: "GENERATE_IN_ESPHOME_DASHBOARD"
ota_password: "YourOTAPassword"
```

### Tuning Guide
All `# TUNE:` comments indicate adjustable values. To change:
1. Edit number in YAML
2. Save in ESPHome dashboard
3. Click Install → Wirelessly
4. Node updates automatically

---

## 2. NODE-A1: Garden Controller

```yaml
# SENSORS
sensor:
  - platform: adc
    pin: GPIO34
    name: "Soil Moisture A"
    id: soil_a
    unit_of_measurement: "%"
    update_interval: 30s
    attenuation: auto
    filters:
      - calibrate_linear:
          - 3500 -> 0.0    # TUNE: Dry ADC value
          - 1500 -> 100.0  # TUNE: Wet ADC value
      - clamp: {min_value: 0, max_value: 100}

  - platform: adc
    pin: GPIO35
    name: "Soil Moisture B"
    id: soil_b
    unit_of_measurement: "%"
    update_interval: 30s
    attenuation: auto
    filters:
      - calibrate_linear:
          - 3500 -> 0.0
          - 1500 -> 100.0
      - clamp: {min_value: 0, max_value: 100}

  - platform: adc
    pin: GPIO32
    name: "Soil Moisture C"
    id: soil_c
    unit_of_measurement: "%"
    update_interval: 30s
    attenuation: auto
    filters:
      - calibrate_linear:
          - 3500 -> 0.0
          - 1500 -> 100.0
      - clamp: {min_value: 0, max_value: 100}

  - platform: adc
    pin: GPIO33
    name: "Garden Light Level"
    id: light_level
    unit_of_measurement: "%"
    update_interval: 10s
    attenuation: auto
    filters:
      - calibrate_linear:
          - 0 -> 100.0
          - 4095 -> 0.0
      - clamp: {min_value: 0, max_value: 100}

binary_sensor:
  - platform: gpio
    pin: GPIO23
    name: "Garden Motion"
    id: garden_motion
    device_class: motion
    filters:
      - delayed_off: 5s    # TUNE: Motion timeout

  - platform: gpio
    pin: GPIO25
    name: "Rain Detected"
    id: rain_detected
    device_class: moisture
    filters:
      - delayed_on: 3s     # TUNE: Rain confirmation

switch:
  - platform: gpio
    pin: GPIO19
    name: "Water Valve A"
    id: valve_a
    icon: "mdi:water-pump"
    interlock: [valve_b, valve_c]
    on_turn_on:
      - delay: 10s         # TUNE: Watering duration
      - switch.turn_off: valve_a

  - platform: gpio
    pin: GPIO18
    name: "Water Valve B"
    id: valve_b
    icon: "mdi:water-pump"
    interlock: [valve_a, valve_c]
    on_turn_on:
      - delay: 10s
      - switch.turn_off: valve_b

  - platform: gpio
    pin: GPIO5
    name: "Water Valve C"
    id: valve_c
    icon: "mdi:water-pump"
    interlock: [valve_a, valve_b]
    on_turn_on:
      - delay: 10s
      - switch.turn_off: valve_c

  - platform: gpio
    pin: GPIO16
    name: "Garden Light"
    id: garden_light
    icon: "mdi:lightbulb-outdoor"

output:
  - platform: ledc
    pin: GPIO26
    id: awning_fwd
    frequency: 1000Hz
  - platform: ledc
    pin: GPIO27
    id: awning_rev
    frequency: 1000Hz

fan:
  - platform: speed
    output: awning_fwd
    name: "Awning Motor"
    id: awning_motor
    direction_output: awning_rev
    speed_count: 3

# AUTO-WATER: soil dry AND no rain
interval:
  - interval: 5min
    then:
      - if:
          condition:
            and:
              - sensor.in_range: {id: soil_a, below: 30.0}  # TUNE
              - binary_sensor.is_off: rain_detected
          then:
            - switch.turn_on: valve_a
            - delay: 2s
      - if:
          condition:
            and:
              - sensor.in_range: {id: soil_b, below: 30.0}
              - binary_sensor.is_off: rain_detected
          then:
            - switch.turn_on: valve_b
            - delay: 2s
      - if:
          condition:
            and:
              - sensor.in_range: {id: soil_c, below: 30.0}
              - binary_sensor.is_off: rain_detected
          then:
            - switch.turn_on: valve_c

# DUSK-TO-DAWN + Motion
interval:
  - interval: 10s
    then:
      - if:
          condition:
            and:
              - sensor.in_range: {id: light_level, below: 20.0}  # TUNE
              - binary_sensor.is_on: garden_motion
          then:
            - switch.turn_on: garden_light
      - if:
          condition:
            sensor.in_range: {id: light_level, above: 40.0}    # TUNE
          then:
            - switch.turn_off: garden_light
```

---

## 3. NODE-B1: Kitchen Safety (CRITICAL)

```yaml
sensor:
  - platform: adc
    pin: GPIO34
    name: "Kitchen Gas Level"
    id: gas_level
    unit_of_measurement: "ppm"
    update_interval: 2s
    attenuation: auto
    filters:
      - sliding_window_moving_average: {window_size: 10, send_every: 5}
      - calibrate_linear:
          - 500 -> 0.0     # TUNE: Clean air
          - 3000 -> 1000.0 # TUNE: Danger
      - clamp: {min_value: 0}

  - platform: adc
    pin: GPIO35
    name: "Kitchen Smoke Level"
    id: smoke_level
    unit_of_measurement: "ppm"
    update_interval: 2s
    attenuation: auto
    filters:
      - sliding_window_moving_average: {window_size: 10, send_every: 5}
      - calibrate_linear:
          - 400 -> 0.0
          - 2500 -> 1000.0
      - clamp: {min_value: 0}

  - platform: dht
    pin: GPIO21
    temperature:
      name: "Kitchen Temperature"
      id: kitchen_temp
    humidity:
      name: "Kitchen Humidity"
      id: kitchen_humidity
    update_interval: 10s
    model: dht22

binary_sensor:
  - platform: gpio
    pin:
      number: GPIO22
      mode: {input: true, pullup: true}
    name: "Kitchen Water Leak"
    id: kitchen_leak
    device_class: moisture
    filters:
      - delayed_on: 2s    # TUNE
    on_press:
      then:
        - switch.turn_on: water_valve
        - switch.turn_on: kitchen_siren
        - homeassistant.event:
            event: esphome.water_leak
            data: {location: "kitchen"}

  - platform: template
    name: "Gas Leak Alert"
    id: gas_alert
    device_class: gas
    lambda: 'return id(gas_level).state > 500.0;'  # TUNE: threshold
    on_press:
      then:
        - switch.turn_on: exhaust_fan
        - delay: 500ms
        - switch.turn_on: gas_valve
        - delay: 500ms
        - switch.turn_on: kitchen_siren
        - homeassistant.event:
            event: esphome.gas_leak
            data:
              location: "kitchen"
              level: !lambda 'return id(gas_level).state;'

  - platform: template
    name: "Smoke Alert"
    id: smoke_alert
    device_class: smoke
    lambda: 'return id(smoke_level).state > 400.0;'  # TUNE
    on_press:
      then:
        - switch.turn_on: exhaust_fan
        - delay: 500ms
        - switch.turn_on: kitchen_siren
        - homeassistant.event:
            event: esphome.smoke_detected
            data: {location: "kitchen"}

switch:
  - platform: gpio
    pin: GPIO19
    name: "Kitchen Exhaust"
    id: exhaust_fan
    icon: "mdi:fan"
    restore_mode: ALWAYS_OFF

  - platform: gpio
    pin: GPIO18
    name: "Gas Valve Cutoff"
    id: gas_valve
    icon: "mdi:valve-closed"
    restore_mode: ALWAYS_OFF
    inverted: true

  - platform: gpio
    pin: GPIO5
    name: "Kitchen Water Cutoff"
    id: water_valve
    icon: "mdi:water-off"
    restore_mode: ALWAYS_OFF
    inverted: true

  - platform: gpio
    pin: GPIO16
    name: "Kitchen Siren"
    id: kitchen_siren
    icon: "mdi:alarm-light"
    restore_mode: ALWAYS_OFF

# AUTO EXHAUST ON HIGH HUMIDITY
sensor:
  - platform: dht
    pin: GPIO21
    humidity:
      name: "Kitchen Humidity"
      id: kitchen_humidity
      on_value_range:
        - above: 70.0     # TUNE: Exhaust ON
          then:
            - switch.turn_on: exhaust_fan
        - below: 55.0      # TUNE: Exhaust OFF
          then:
            - switch.turn_off: exhaust_fan
```

---

## 4. NODE-C1: Water Tank & Pump

```yaml
binary_sensor:
  - platform: gpio
    pin: {number: GPIO23, mode: {input: true, pullup: true}}
    name: "OH Tank Empty"
    id: oh_empty
    device_class: moisture

  - platform: gpio
    pin: {number: GPIO22, mode: {input: true, pullup: true}}
    name: "OH Tank Mid"
    id: oh_mid
    device_class: moisture

  - platform: gpio
    pin: {number: GPIO21, mode: {input: true, pullup: true}}
    name: "OH Tank Full"
    id: oh_full
    device_class: moisture

  - platform: gpio
    pin: {number: GPIO19, mode: {input: true, pullup: true}}
    name: "Sump Low"
    id: sump_low
    device_class: moisture

  - platform: gpio
    pin: {number: GPIO18, mode: {input: true, pullup: true}}
    name: "Sump Full"
    id: sump_full
    device_class: moisture

sensor:
  - platform: ultrasonic
    trigger_pin: GPIO5
    echo_pin: GPIO16
    name: "OH Tank Level"
    id: oh_level_ultra
    unit_of_measurement: "%"
    filters:
      - lambda: >-
          float tank_height = 120.0;  # TUNE: cm
          float percent = ((tank_height - (x * 100)) / tank_height) * 100.0;
          if (percent < 0) percent = 0;
          if (percent > 100) percent = 100;
          return percent;
      - sliding_window_moving_average: {window_size: 5, send_every: 3}
    update_interval: 10s

  - platform: adc
    pin: GPIO34
    name: "Pump Current"
    id: pump_current
    unit_of_measurement: "A"
    update_interval: 1s
    attenuation: auto
    filters:
      - lambda: >-
          float voltage = x * 3.3;
          float current = (voltage - 1.65) / 0.100;  # TUNE: 20A module
          if (current < 0.1) current = 0;
          return current;
      - sliding_window_moving_average: {window_size: 10, send_every: 5}

switch:
  - platform: gpio
    pin: GPIO25
    name: "Main Water Pump"
    id: main_pump
    icon: "mdi:pump"
    restore_mode: ALWAYS_OFF
    interlock: [pressure_pump]

  - platform: gpio
    pin: GPIO26
    name: "Pressure Pump"
    id: pressure_pump
    icon: "mdi:pump"
    restore_mode: ALWAYS_OFF
    interlock: [main_pump]

# AUTO PUMP LOGIC
interval:
  - interval: 10s
    then:
      - if:
          condition:
            and:
              - binary_sensor.is_on: oh_empty
              - binary_sensor.is_off: sump_low
              - switch.is_off: main_pump
              - sensor.in_range: {id: pump_current, below: 0.5}
          then:
            - switch.turn_on: main_pump
            - delay: 5s
            - if:
                condition:
                  sensor.in_range: {id: pump_current, below: 0.3}  # TUNE: dry run
                then:
                  - switch.turn_off: main_pump
                  - homeassistant.event:
                      event: esphome.dry_run_detected
                      data: {pump: "main"}

      - if:
          condition:
            or:
              - binary_sensor.is_on: oh_full
              - binary_sensor.is_on: sump_low
          then:
            - switch.turn_off: main_pump

# DRY RUN PROTECTION
sensor:
  - platform: adc
    pin: GPIO34
    name: "Pump Current"
    id: pump_current
    on_value_range:
      - below: 0.2          # TUNE: Dry run current
        above: 0.0
        then:
          - if:
              condition:
                switch.is_on: main_pump
              then:
                - switch.turn_off: main_pump
                - homeassistant.event:
                    event: esphome.dry_run_alert
                    data:
                      pump: "main"
                      current: !lambda 'return id(pump_current).state;'
```

---

## 5. NODE-D1: Living Room Comfort

```yaml
sensor:
  - platform: adc
    pin: GPIO34
    name: "Living Room Light"
    id: living_light
    unit_of_measurement: "%"
    update_interval: 5s
    attenuation: auto
    filters:
      - calibrate_linear:
          - 0 -> 100.0
          - 4095 -> 0.0

  - platform: dht
    pin: GPIO21
    temperature:
      name: "Living Room Temperature"
      id: living_temp
    humidity:
      name: "Living Room Humidity"
      id: living_humidity
    update_interval: 30s
    model: dht22

binary_sensor:
  - platform: gpio
    pin: GPIO23
    name: "Living Motion 1"
    id: motion_1
    device_class: motion
    filters:
      - delayed_off: 30s    # TUNE

  - platform: gpio
    pin: GPIO22
    name: "Living Motion 2"
    id: motion_2
    device_class: motion
    filters:
      - delayed_off: 30s

  - platform: gpio
    pin: {number: GPIO19, mode: {input: true, pullup: true}}
    name: "Living Room Door"
    id: living_door
    device_class: door

  - platform: gpio
    pin: {number: GPIO18, mode: {input: true, pullup: true}}
    name: "Living Room Window"
    id: living_window
    device_class: window

switch:
  - platform: gpio
    pin: GPIO16
    name: "Living Room Light"
    id: living_light_sw
    icon: "mdi:lightbulb"
    restore_mode: RESTORE_DEFAULT_OFF

remote_transmitter:
  pin: GPIO17
  carrier_duty_percent: 50%

stepper:
  - platform: a4988
    id: curtain_motor
    step_pin: GPIO26
    dir_pin: GPIO27
    max_speed: 250 steps/s   # TUNE
    sleep_pin: GPIO25
    acceleration: 100
    deceleration: 100

cover:
  - platform: template
    name: "Living Room Curtain"
    id: living_curtain
    device_class: curtain
    optimistic: true
    open_action:
      - stepper.set_target: {id: curtain_motor, target: 4096}  # TUNE
    close_action:
      - stepper.set_target: {id: curtain_motor, target: 0}
    stop_action:
      - stepper.stop: curtain_motor

# AUTO LIGHT
interval:
  - interval: 5s
    then:
      - if:
          condition:
            and:
              - or:
                  - binary_sensor.is_on: motion_1
                  - binary_sensor.is_on: motion_2
              - sensor.in_range: {id: living_light, below: 25.0}  # TUNE
          then:
            - switch.turn_on: living_light_sw

binary_sensor:
  - platform: template
    name: "Living Any Motion"
    id: any_motion
    lambda: 'return id(motion_1).state || id(motion_2).state;'
    on_release:
      then:
        - delay: 5min         # TUNE: Light off delay
        - switch.turn_off: living_light_sw
```

---

## 6. NODE-E1: Master Bathroom

```yaml
sensor:
  - platform: dht
    pin: GPIO21
    temperature:
      name: "Bathroom Temperature"
      id: bath_temp
    humidity:
      name: "Bathroom Humidity"
      id: bath_humidity
    update_interval: 10s
    model: dht22

  - platform: dallas
    address: 0x1234567890123456  # TUNE: Your address
    name: "Geyser Temperature"
    id: geyser_temp
    unit_of_measurement: "°C"
    update_interval: 10s

dallas:
  - pin: GPIO4
    update_interval: 10s

binary_sensor:
  - platform: gpio
    pin: GPIO23
    name: "Bathroom Motion"
    id: bath_motion
    device_class: motion
    filters:
      - delayed_off: 5min    # TUNE
    on_press:
      then:
        - switch.turn_on: bath_light
    on_release:
      then:
        - delay: 3min         # TUNE
        - switch.turn_off: bath_light

  - platform: gpio
    pin: {number: GPIO22, mode: {input: true, pullup: true}}
    name: "Bathroom Water Leak"
    id: bath_leak
    device_class: moisture
    on_press:
      then:
        - switch.turn_on: bath_water_valve
        - homeassistant.event:
            event: esphome.water_leak
            data: {location: "master_bathroom"}

switch:
  - platform: gpio
    pin: GPIO19
    name: "Bathroom Exhaust"
    id: bath_exhaust
    icon: "mdi:fan"

  - platform: gpio
    pin: GPIO18
    name: "Geyser Power"
    id: geyser_relay
    icon: "mdi:water-boiler"
    restore_mode: ALWAYS_OFF

  - platform: gpio
    pin: GPIO5
    name: "Bathroom Water Cutoff"
    id: bath_water_valve
    icon: "mdi:water-off"
    restore_mode: ALWAYS_OFF
    inverted: true

  - platform: gpio
    pin: GPIO16
    name: "Bathroom Light"
    id: bath_light
    icon: "mdi:lightbulb"
    restore_mode: RESTORE_DEFAULT_OFF

# AUTO EXHAUST
sensor:
  - platform: dht
    pin: GPIO21
    humidity:
      name: "Bathroom Humidity"
      id: bath_humidity
      on_value_range:
        - above: 75.0       # TUNE: Exhaust ON
          then:
            - switch.turn_on: bath_exhaust
        - below: 60.0        # TUNE: Exhaust OFF
          then:
            - switch.turn_off: bath_exhaust

# GEYSER SAFETY
sensor:
  - platform: dallas
    address: 0x1234567890123456
    name: "Geyser Temperature"
    id: geyser_temp
    on_value_range:
      - above: 60.0          # TUNE: Max safe temp
        then:
          - switch.turn_off: geyser_relay
          - homeassistant.event:
              event: esphome.geyser_overheat
              data:
                temperature: !lambda 'return id(geyser_temp).state;'
```

---

## 7. NODE-F1: Night Security Camera

```yaml
esp32:
  board: esp32cam

esp32_camera:
  external_clock:
    pin: GPIO0
    frequency: 20MHz
  i2c_pins:
    sda: GPIO26
    scl: GPIO27
  data_pins: [GPIO5, GPIO18, GPIO19, GPIO36, GPIO39, GPIO34, GPIO35, GPIO32]
  vsync_pin: GPIO25
  href_pin: GPIO23
  pixel_clock_pin: GPIO22
  power_down_pin: GPIO32
  resolution: 640x480       # TUNE
  jpeg_quality: 10          # TUNE: lower=better
  max_framerate: 5 fps      # TUNE
  idle_framerate: 0.2 fps   # TUNE

esp32_camera_web_server:
  port: 8080
  stream_source: camera

sd_card:
  id: sd_card_storage
  clk_pin: GPIO14
  cmd_pin: GPIO15
  dat0_pin: GPIO2
  mode: 1bit

binary_sensor:
  - platform: gpio
    pin: GPIO13
    name: "Camera Motion"
    id: cam_motion
    device_class: motion
    filters:
      - delayed_off: 10s
    on_press:
      then:
        - output.turn_on: ir_led
        - delay: 30s         # TUNE: IR on duration
        - output.turn_off: ir_led
        - homeassistant.event:
            event: esphome.camera_motion
            data: {camera: "night_security"}

output:
  - platform: gpio
    pin: GPIO4
    id: ir_led
```

---

## 8. NODE-F3: Intrusion Alarm

```yaml
binary_sensor:
  - platform: gpio
    pin: {number: GPIO23, mode: {input: true, pullup: true}}
    name: "Front Door"
    id: front_door
    device_class: door
    on_press:
      then:
        - if:
            condition:
              switch.is_on: alarm_armed
            then:
              - homeassistant.event:
                  event: esphome.alarm_entry_delay
                  data: {zone: "front_door", delay_seconds: 30}  # TUNE

  - platform: gpio
    pin: {number: GPIO22, mode: {input: true, pullup: true}}
    name: "Back Door"
    id: back_door
    device_class: door

  - platform: gpio
    pin: {number: GPIO21, mode: {input: true, pullup: true}}
    name: "Living Room Window"
    id: lr_window
    device_class: window
    on_press:
      then:
        - if:
            condition:
              switch.is_on: alarm_armed
            then:
              - switch.turn_on: alarm_siren
              - homeassistant.event:
                  event: esphome.alarm_triggered
                  data: {zone: "living_room_window", type: "perimeter"}

  - platform: gpio
    pin: {number: GPIO19, mode: {input: true, pullup: true}}
    name: "Bedroom Window"
    id: bed_window
    device_class: window

  - platform: gpio
    pin: GPIO18
    name: "Hallway Motion"
    id: hall_motion
    device_class: motion
    filters:
      - delayed_off: 5s
    on_press:
      then:
        - if:
            condition:
              switch.is_on: alarm_armed
            then:
              - switch.turn_on: alarm_siren
              - homeassistant.event:
                  event: esphome.alarm_triggered
                  data: {zone: "hallway", type: "interior"}

  - platform: gpio
    pin: GPIO5
    name: "Living Room Motion"
    id: lr_motion_alarm
    device_class: motion
    filters:
      - delayed_off: 5s

  - platform: gpio
    pin: {number: GPIO16, mode: {input: true, pullup: true}}
    name: "Glass Break"
    id: glass_break
    device_class: vibration
    filters:
      - delayed_on: 500ms    # TUNE
    on_press:
      then:
        - if:
            condition:
              switch.is_on: alarm_armed
            then:
              - switch.turn_on: alarm_siren
              - homeassistant.event:
                  event: esphome.alarm_triggered
                  data: {zone: "glass", type: "perimeter"}

switch:
  - platform: template
    name: "Alarm Armed"
    id: alarm_armed
    optimistic: true
    restore_mode: RESTORE_DEFAULT_OFF

  - platform: gpio
    pin: GPIO17
    name: "Alarm Siren"
    id: alarm_siren
    icon: "mdi:alarm-light"
    restore_mode: ALWAYS_OFF
```

---

## 9. NODE-G2: Air Quality

```yaml
uart:
  - id: uart_pms
    rx_pin: GPIO16
    tx_pin: GPIO17
    baud_rate: 9600
  - id: uart_mhz
    rx_pin: GPIO18
    tx_pin: GPIO19
    baud_rate: 9600

i2c:
  - id: bus_a
    sda: GPIO21
    scl: GPIO22
    scan: true

sensor:
  - platform: pmsx003
    type: PMSX003
    uart_id: uart_pms
    pm_1_0: {name: "PM1.0", id: pm1_0}
    pm_2_5: {name: "PM2.5", id: pm2_5}
    pm_10_0: {name: "PM10", id: pm10_0}
    update_interval: 30s

  - platform: mhz19
    uart_id: uart_mhz
    co2: {name: "CO2", id: co2_level}
    temperature: {name: "MH-Z19 Temp"}
    update_interval: 60s
    automatic_baseline_calibration: false  # TUNE

  - platform: ccs811
    i2c_id: bus_a
    eco2: {name: "eCO2", id: eco2_level}
    tvoc: {name: "TVOC", id: tvoc_level}
    update_interval: 60s
    baseline: 0x1234  # TUNE: After 48h burn-in

switch:
  - platform: gpio
    pin: GPIO23
    name: "Ventilation"
    id: ventilation
    icon: "mdi:air-purifier"

sensor:
  - platform: pmsx003
    pm_2_5:
      name: "PM2.5"
      id: pm2_5
      on_value_range:
        - above: 35.0       # TUNE: Unhealthy
          then:
            - switch.turn_on: ventilation
        - below: 15.0        # TUNE: Good
          then:
            - switch.turn_off: ventilation

  - platform: mhz19
    co2:
      name: "CO2"
      id: co2_level
      on_value_range:
        - above: 1000.0     # TUNE: High CO2
          then:
            - switch.turn_on: ventilation
        - below: 600.0
          then:
            - switch.turn_off: ventilation
```

---

## 10. NODE-H1: Aquarium

```yaml
dallas:
  - pin: GPIO4
    update_interval: 10s

sensor:
  - platform: dallas
    address: 0x1234567890123456  # TUNE
    name: "Aquarium Temperature"
    id: aqua_temp
    unit_of_measurement: "°C"
    on_value_range:
      - below: 24.0           # TUNE: Min temp
        then:
          - switch.turn_on: heater
      - above: 27.0           # TUNE: Max temp
        then:
          - switch.turn_off: heater

  - platform: adc
    pin: GPIO34
    name: "Water TDS"
    id: water_tds
    unit_of_measurement: "ppm"
    update_interval: 60s
    attenuation: auto
    filters:
      - calibrate_linear:
          - 0 -> 0
          - 3.3 -> 1000       # TUNE: Calibrate with TDS meter

binary_sensor:
  - platform: gpio
    pin: {number: GPIO23, mode: {input: true, pullup: true}}
    name: "Aquarium Water Low"
    id: aqua_low
    device_class: moisture
    on_press:
      then:
        - switch.turn_on: topup_pump
    on_release:
      then:
        - delay: 3s
        - switch.turn_off: topup_pump

switch:
  - platform: gpio
    pin: GPIO19
    name: "Aquarium Heater"
    id: heater
    icon: "mdi:heating-coil"
    restore_mode: ALWAYS_OFF

  - platform: gpio
    pin: GPIO18
    name: "Aquarium Light"
    id: aqua_light
    icon: "mdi:lightbulb"
    restore_mode: ALWAYS_OFF

  - platform: gpio
    pin: GPIO5
    name: "Filter Pump"
    id: filter_pump
    icon: "mdi:pump"
    restore_mode: ALWAYS_ON  # TUNE: Keep running

  - platform: gpio
    pin: GPIO16
    name: "Top-up Pump"
    id: topup_pump
    icon: "mdi:water-pump"
    restore_mode: ALWAYS_OFF

servo:
  - id: fish_feeder
    output: pwm_servo

output:
  - platform: ledc
    id: pwm_servo
    pin: GPIO17
    frequency: 50Hz

interval:
  - interval: 12h            # TUNE: Feed every 12h
    then:
      - servo.write: {id: fish_feeder, level: 50.0%}  # TUNE
      - delay: 1s
      - servo.write: {id: fish_feeder, level: 0.0%}
```

---

## 11. NODE-S1: Electrical Monitor

```yaml
uart:
  rx_pin: GPIO16
  tx_pin: GPIO17
  baud_rate: 9600

sensor:
  - platform: pzemac
    voltage: {name: "Mains Voltage", id: mains_voltage}
    current: {name: "Mains Current", id: mains_current}
    power: {name: "Mains Power", id: mains_power}
    energy: {name: "Mains Energy", id: mains_energy}
    frequency: {name: "Mains Frequency", id: mains_freq}
    power_factor: {name: "Power Factor", id: pf}
    update_interval: 5s

switch:
  - platform: gpio
    pin: GPIO19
    name: "Emergency Mains Cutoff"
    id: mains_cutoff
    icon: "mdi:electric-switch-closed"
    restore_mode: ALWAYS_OFF
    inverted: true

sensor:
  - platform: pzemac
    voltage:
      name: "Mains Voltage"
      id: mains_voltage
      on_value_range:
        - below: 180.0       # TUNE: Undervoltage
          then:
            - switch.turn_on: mains_cutoff
            - homeassistant.event:
                event: esphome.undervoltage
                data: {voltage: !lambda 'return id(mains_voltage).state;'}
        - above: 260.0        # TUNE: Overvoltage
          then:
            - switch.turn_on: mains_cutoff
            - homeassistant.event:
                event: esphome.overvoltage
                data: {voltage: !lambda 'return id(mains_voltage).state;'}
    current:
      name: "Mains Current"
      id: mains_current
      on_value_range:
        - above: 25.0         # TUNE: Overcurrent
          then:
            - switch.turn_on: mains_cutoff
            - homeassistant.event:
                event: esphome.overcurrent
                data: {current: !lambda 'return id(mains_current).state;'}
    power:
      name: "Mains Power"
      id: mains_power
      on_value_range:
        - above: 5500.0        # TUNE: Overload
          then:
            - switch.turn_on: mains_cutoff
            - homeassistant.event:
                event: esphome.overload
                data: {power: !lambda 'return id(mains_power).state;'}
```

---

## 12. NODE-S3: Panic Button

```yaml
esp8266:
  board: nodemcuv2

logger:
  level: INFO
  baud_rate: 0

binary_sensor:
  - platform: gpio
    pin: {number: GPIO0, mode: {input: true, pullup: true}}
    name: "Panic Button"
    id: panic_btn
    device_class: safety
    filters:
      - delayed_on: 500ms     # TUNE: Hold time
    on_press:
      then:
        - homeassistant.event:
            event: esphome.panic_pressed
            data:
              location: "ground_floor"
              timestamp: !lambda 'return id(homeassistant_time).now().timestamp();'

sensor:
  - platform: adc
    pin: A0
    name: "Panic Battery"
    id: panic_battery
    unit_of_measurement: "%"
    update_interval: 1h
    filters:
      - lambda: >-
          float voltage = x * 3.3;
          float percent = (voltage - 3.0) / (4.2 - 3.0) * 100.0;
          if (percent > 100) percent = 100;
          if (percent < 0) percent = 0;
          return percent;

deep_sleep:
  run_duration: 30s
  sleep_duration: 1h
  wakeup_pin: GPIO0
  wakeup_pin_mode: KEEP_AWAKE

time:
  - platform: homeassistant
    id: homeassistant_time
```

---

## 13. NODE-S5: Fire Detection

```yaml
esp8266:
  board: nodemcuv2

sensor:
  - platform: adc
    pin: A0
    name: "Smoke Level"
    id: smoke_level_gf
    unit_of_measurement: "ppm"
    update_interval: 2s
    filters:
      - sliding_window_moving_average: {window_size: 10, send_every: 5}
      - calibrate_linear:
          - 400 -> 0.0
          - 2500 -> 1000.0
      - clamp: {min_value: 0}

binary_sensor:
  - platform: template
    name: "Fire Detected"
    id: fire_alert_gf
    device_class: smoke
    lambda: 'return id(smoke_level_gf).state > 300.0;'  # TUNE
    on_press:
      then:
        - output.turn_on: buzzer
        - homeassistant.event:
            event: esphome.fire_detected
            data:
              location: "ground_floor"
              level: !lambda 'return id(smoke_level_gf).state;'
    on_release:
      then:
        - output.turn_off: buzzer

output:
  - platform: gpio
    pin: GPIO2
    id: buzzer
    inverted: true
```

---

## 14. secrets.yaml Template

```yaml
# Store in ESPHome addon: /config/esphome/secrets.yaml
# NEVER commit to Git!

wifi_ssid: "SmartHome_IoT"
wifi_password: "YourStrongWiFiPassword"
api_key: "YOUR_GENERATED_API_KEY"
ota_password: "YourOTAPassword"
```

---

## 15. OTA & Troubleshooting

### How to Update OTA
1. ESPHome dashboard → Find node → Edit → Save → Install → Wirelessly
2. Node downloads and flashes automatically

### Troubleshooting
| Problem | Solution |
|---------|----------|
| OTA fails | Press reset button, try again. Check WiFi signal. |
| Binary too large | Disable logger, reduce image size |
| DS18B20 not found | Check address, wiring, 4.7kΩ pull-up |
| DHT22 shows NaN | Check wiring, add 10kΩ pull-up, increase power |
| Relay not triggering | Check if ACTIVE LOW, invert in YAML if needed |
| ADC values wrong | Check attenuation setting, verify voltage divider |
| MQTT not connecting | Verify broker IP, check firewall, test with mosquitto_pub |

### How to Find DS18B20 Address
Flash temporary YAML with `address: 0x0000000000000000` — logs print all found addresses.

### How to Learn IR Codes
Use `remote_receiver` with `dump: all` — press remote buttons, check logs for hex codes.

---

*End of 06_ESPHome_YAML_Configurations_All_Nodes.md*
*Next: 07_Home_Assistant_Configuration_and_Dashboard.md*
