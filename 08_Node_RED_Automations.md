# 08_Node_RED_Automations.md
# SmartHome Prototype — Node-RED Flows & Complex Logic

**Version:** 1.0 | **Date:** August 2026

---

## Table of Contents
1. [Node-RED Setup](#1-node-red-setup)
2. [Flow 1: Gas Leak Emergency Sequence](#flow-1-gas-leak-emergency-sequence)
3. [Flow 2: Intrusion Alarm Logic](#flow-2-intrusion-alarm-logic)
4. [Flow 3: Water Tank Smart Pump Control](#flow-3-water-tank-smart-pump-control)
5. [Flow 4: Scene Controller](#flow-4-scene-controller)
6. [Flow 5: Predictive Maintenance](#flow-5-predictive-maintenance)
7. [Flow 6: Energy Peak Load Management](#flow-6-energy-peak-load-management)
8. [Flow 7: Voice Command Handler](#flow-7-voice-command-handler)
9. [Flow 8: Telegram Bot Alerts](#flow-8-telegram-bot-alerts)
10. [Flow Export/Import Guide](#flow-exportimport-guide)

---

## 1. Node-RED Setup

### Access
URL: `http://192.168.1.10:1880`

### Install Nodes
Menu → Manage Palette → Install:
- `node-red-contrib-home-assistant-websocket`
- `node-red-dashboard`
- `node-red-node-telegrambot`
- `node-red-node-email`

### Connect to Home Assistant
1. Install "Node-RED Companion" in HA (via HACS)
2. In Node-RED: Add HA Server node
3. Base URL: `http://192.168.1.10:8123`
4. Access Token: HA → Profile → Long-Lived Access Tokens → Create

---

## Flow 1: Gas Leak Emergency Sequence

**Purpose:** Multi-step emergency response with escalation

```
[HA Event: esphome.gas_leak]
         │
         ▼
[Function: Parse payload]
         │
         ▼
[Switch: Location?]
    ├─ kitchen ──► [Call Service: notify.mobile_app]
    │              [Call Service: switch.turn_on exhaust]
    │              [Call Service: switch.turn_on gas_valve]
    │              [Delay: 2s]
    │              [Call Service: switch.turn_on siren]
    │              [Delay: 30s]
    │              [Call Service: notify.mobile_app]
    │              msg: "Gas still detected! Evacuate!"
    │
    └─ other ────► [Call Service: notify.mobile_app]
                   [Call Service: switch.turn_on siren]
```

### JSON Export
```json
[
    {
        "id": "gas_leak_trigger",
        "type": "server-events",
        "z": "flow1",
        "name": "Gas Leak Event",
        "server": "home_assistant",
        "event": "esphome.gas_leak",
        "x": 150,
        "y": 100,
        "wires": [["parse_gas"]]
    },
    {
        "id": "parse_gas",
        "type": "function",
        "z": "flow1",
        "name": "Parse Payload",
        "func": "msg.location = msg.payload.event.location;
msg.level = msg.payload.event.level;
msg.topic = 'GAS LEAK: ' + msg.location;
return msg;",
        "outputs": 1,
        "x": 350,
        "y": 100,
        "wires": [["gas_notify"]]
    },
    {
        "id": "gas_notify",
        "type": "api-call-service",
        "z": "flow1",
        "name": "Notify Phone",
        "server": "home_assistant",
        "service": "notify.mobile_app_your_phone",
        "data": "{"title":"🚨 GAS LEAK","message":"Gas detected in {{location}}. Level: {{level}} ppm","data":{"priority":"high","ttl":0}}",
        "x": 550,
        "y": 100,
        "wires": [["gas_exhaust"]]
    },
    {
        "id": "gas_exhaust",
        "type": "api-call-service",
        "z": "flow1",
        "name": "Turn ON Exhaust",
        "server": "home_assistant",
        "service": "switch.turn_on",
        "data": "{"entity_id":"switch.kitchen_exhaust"}",
        "x": 750,
        "y": 100,
        "wires": [["gas_valve"]]
    },
    {
        "id": "gas_valve",
        "type": "api-call-service",
        "z": "flow1",
        "name": "Close Gas Valve",
        "server": "home_assistant",
        "service": "switch.turn_on",
        "data": "{"entity_id":"switch.gas_valve_cutoff"}",
        "x": 950,
        "y": 100,
        "wires": [["gas_siren"]]
    },
    {
        "id": "gas_siren",
        "type": "api-call-service",
        "z": "flow1",
        "name": "Sound Siren",
        "server": "home_assistant",
        "service": "switch.turn_on",
        "data": "{"entity_id":"switch.kitchen_siren"}",
        "x": 1150,
        "y": 100,
        "wires": [["gas_delay"]]
    },
    {
        "id": "gas_delay",
        "type": "delay",
        "z": "flow1",
        "name": "Wait 30s",
        "pauseType": "delay",
        "timeout": "30",
        "timeoutUnits": "seconds",
        "x": 1350,
        "y": 100,
        "wires": [["gas_escalate"]]
    },
    {
        "id": "gas_escalate",
        "type": "api-call-service",
        "z": "flow1",
        "name": "Escalation Alert",
        "server": "home_assistant",
        "service": "notify.mobile_app_your_phone",
        "data": "{"title":"🚨 GAS STILL DETECTED","message":"Gas levels still high. Evacuate immediately!","data":{"priority":"high"}}",
        "x": 1550,
        "y": 100,
        "wires": []
    }
]
```

---

## Flow 2: Intrusion Alarm Logic

**Purpose:** Entry delay, instant triggers, auto-arm/disarm

```
[HA Event: esphome.alarm_entry_delay]
         │
         ▼
[Function: Start 30s timer]
         │
         ▼
[Delay: 30s]
         │
         ▼
[Switch: Alarm still armed?]
    ├─ YES ──► [Call Service: switch.turn_on siren]
    │          [Call Service: notify.mobile_app]
    │          msg: "ALARM TRIGGERED!"
    │
    └─ NO ───► [Debug: "Disarmed in time"]

[HA Event: esphome.alarm_triggered]
         │
         ▼
[Function: Instant trigger]
         │
         ▼
[Call Service: switch.turn_on siren]
[Call Service: notify.mobile_app]
[Call Service: camera.snapshot]
```

---

## Flow 3: Water Tank Smart Pump Control

**Purpose:** Smart scheduling, dry-run protection, pressure boost

```
[HA State: binary_sensor.oh_tank_empty = ON]
         │
         ▼
[Function: Check conditions]
    ├─ Sump not low? ──► YES
    ├─ Not in dry-run? ─► YES
    ├─ Not nighttime? ──► YES (optional)
         │
         ▼
[Call Service: switch.turn_on main_pump]
         │
         ▼
[Delay: 5s]
         │
         ▼
[HA State: sensor.pump_current]
         │
         ▼
[Switch: Current > 0.3A?]
    ├─ YES ──► [Debug: "Pump running normally"]
    │
    └─ NO ───► [Call Service: switch.turn_off main_pump]
               [Call Service: notify.mobile_app]
               msg: "Dry run detected!"
               [Function: Set dry_run_flag = true]

[HA State: binary_sensor.oh_tank_full = ON]
         │
         ▼
[Call Service: switch.turn_off main_pump]
[Call Service: notify.mobile_app]
msg: "Tank full. Pump stopped."
```

---

## Flow 4: Scene Controller

**Purpose:** Complex scene logic with conditions

```
[Inject: Morning 7:00 AM]
         │
         ▼
[Function: Check weekday]
    ├─ Weekend ──► [Delay: 2 hours] ──► Continue
    └─ Weekday ──► Continue
         │
         ▼
[Call Service: scene.turn_on morning]
[Call Service: cover.open_cover]
[Call Service: switch.turn_on geyser]
[Delay: 30 min]
[Call Service: switch.turn_off geyser]

[Inject: Night 10:30 PM]
         │
         ▼
[Function: Check if anyone home]
    ├─ Home ──► [Call Service: scene.turn_on night]
    │           [Call Service: switch.turn_off geyser]
    │           [Call Service: switch.turn_on alarm_armed]
    │
    └─ Away ──► [Already in away mode]
```

---

## Flow 5: Predictive Maintenance

**Purpose:** Track appliance health, predict failures

```
[Inject: Every hour]
         │
         ▼
[HA State: sensor.pump_current]
[HA State: sensor.mains_power]
         │
         ▼
[Function: Store in context]
    msg.pump_history.push(msg.payload)
    if (msg.pump_history.length > 168) { // 1 week
        msg.pump_history.shift()
    }
         │
         ▼
[Function: Analyze trend]
    avg_current = average(pump_history)
    if (avg_current > baseline * 1.3) {
        msg.alert = "Pump current increasing - possible bearing wear"
    }
         │
         ▼
[Switch: Alert?]
    ├─ YES ──► [Call Service: notify.mobile_app]
    │          msg: "Maintenance alert: {{alert}}"
    └─ NO ───► [Debug: "All normal"]
```

---

## Flow 6: Energy Peak Load Management

**Purpose:** Prevent overload by shedding non-critical loads

```
[HA State: sensor.mains_power]
         │
         ▼
[Switch: Power > 4500W?]
    ├─ YES ──► [Function: Priority list]
    │          1. Turn off geyser
    │          2. Turn off aquarium heater
    │          3. Turn off garden pump
    │          4. Notify: "Load shedding active"
    │
    └─ NO ───► [Switch: Power < 3000W?]
               ├─ YES ──► [Function: Restore loads in reverse]
               └─ NO ───► [Debug: "Normal load"]
```

---

## Flow 7: Voice Command Handler

**Purpose:** Local voice control via Wyoming Protocol

```
[HA Event: wyoming.speech]
         │
         ▼
[Function: Parse text]
    text = msg.payload.text.toLowerCase()
         │
         ▼
[Switch: Command?]
    ├─ "turn on lights" ──► [Call Service: switch.turn_on all_lights]
    ├─ "turn off lights" ─► [Call Service: switch.turn_off all_lights]
    ├─ "good night" ──────► [Call Service: scene.turn_on night]
    ├─ "good morning" ────► [Call Service: scene.turn_on morning]
    ├─ "arm security" ────► [Call Service: switch.turn_on alarm_armed]
    ├─ "disarm security" ─► [Call Service: switch.turn_off alarm_armed]
    ├─ "water the plants" ─► [Call Service: switch.turn_on valve_a]
    │                      [Delay: 10s]
    │                      [Call Service: switch.turn_on valve_b]
    │                      [Delay: 10s]
    │                      [Call Service: switch.turn_on valve_c]
    └─ default ───────────► [Debug: "Unknown command"]
```

---

## Flow 8: Telegram Bot Alerts

**Purpose:** Backup notification channel

```
[Any critical event]
         │
         ▼
[Function: Format message]
    msg.payload = "🚨 *" + msg.topic + "*
"
                + "Location: " + msg.location + "
"
                + "Time: " + new Date().toLocaleString()
         │
         ▼
[Telegram Sender]
    Chat ID: YOUR_CHAT_ID
    Message: {{payload}}
    Parse Mode: Markdown
```

### Setup Telegram Bot
1. Message @BotFather on Telegram
2. Create new bot, get token
3. Message your bot, get chat ID from:
   `https://api.telegram.org/bot<TOKEN>/getUpdates`
4. In Node-RED: Telegram receiver node → get chat ID

---

## Flow Export/Import Guide

### Export
1. Node-RED → Select nodes → Menu → Export → Clipboard
2. Copy JSON
3. Save to GitHub: `nodered/flows.json`

### Import
1. Node-RED → Menu → Import → Clipboard
2. Paste JSON
3. Deploy

### Version Control
```bash
# Export flows automatically
curl -X POST http://192.168.1.10:1880/flows   -H "Content-Type: application/json"   -d @flows.json

# Backup flows
cp /home/youruser/smarthome/nodered/data/flows.json    /home/youruser/smarthome/backups/nodered/
```

---

*End of 08_Node_RED_Automations.md*
*Next: 09_Safety_Guidelines.md*
