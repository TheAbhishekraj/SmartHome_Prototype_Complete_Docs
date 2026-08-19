# 15_README_For_Each_Node.md
# SmartHome Prototype — Per-Node README Templates

**Version:** 1.0 | **Date:** August 2026

---

## README Template (Copy for Each Node)

```markdown
# [NODE-NAME] — [Human Readable Name]

## What This Node Does
[2-3 sentence description]

## Sensors Connected
| Sensor | GPIO | Purpose |
|--------|------|---------|
| [Name] | GPIO[X] | [What it measures] |

## Actuators Connected
| Actuator | GPIO | Purpose |
|----------|------|---------|
| [Name] | GPIO[X] | [What it controls] |

## How to Change Thresholds
Edit these values in the YAML:
- `THRESHOLD_NAME = [value]` — [What it does]

## How to Change Timing
- `DELAY_NAME = [value]ms` — [What it controls]

## How to Change Logic
[Explain which lambda or condition to edit]

## Safety Notes
- [Critical safety information]

## Troubleshooting
| Problem | Cause | Solution |
|---------|-------|----------|
| [Issue] | [Why] | [How to fix] |

## Wiring Diagram
[ASCII or reference to photo]

## Last Updated
[Date] by [Name]
```

---

## Example: NODE-B1 Kitchen Safety README

```markdown
# NODE-B1 — Kitchen Safety Node

## What This Node Does
Monitors kitchen for gas leaks (MQ-6), smoke (MQ-2), and water leaks. Automatically turns on exhaust fan, closes gas valve, sounds siren, and sends mobile alerts when danger is detected.

## Sensors Connected
| Sensor | GPIO | Purpose |
|--------|------|---------|
| MQ-6 Gas | GPIO34 (A0) | LPG detection |
| MQ-2 Smoke | GPIO35 (A0) | Smoke detection |
| DHT22 | GPIO21 | Temperature/humidity |
| Water Leak | GPIO22 | Under-sink leak |

## Actuators Connected
| Actuator | GPIO | Purpose |
|----------|------|---------|
| Exhaust Relay | GPIO19 | Kitchen exhaust fan |
| Gas Valve Relay | GPIO18 | Closes gas supply |
| Water Valve Relay | GPIO5 | Cuts water inlet |
| Siren Relay | GPIO16 | Alarm siren |

## How to Change Thresholds
- `GAS_THRESHOLD = 500` — ppm above which gas leak is declared
- `SMOKE_THRESHOLD = 400` — ppm above which smoke alert triggers
- `HUMIDITY_MAX = 70.0` — % above which auto exhaust turns on

## How to Change Timing
- `ALARM_DURATION = 60000` — Siren runs for 60 seconds (ms)
- `GAS_CONFIRMATION = 3000` — Gas must be high for 3 seconds before alarm

## How to Change Logic
- Gas sequence: Edit `on_press` under `gas_alert` binary_sensor
- To add email alert: Add `homeassistant.event` action or Node-RED flow

## Safety Notes
- MQ-6 needs 24-hour burn-in on first use
- Gas valve is NC (Normally Closed) — relay ON closes valve
- Manual reset required after gas alarm (set pot to 0 in sim, or clear gas in real)
- Test monthly with cigarette lighter gas (briefly, carefully)

## Troubleshooting
| Problem | Cause | Solution |
|---------|-------|----------|
| Gas sensor always high | Not burned in | Leave powered for 24 hours |
| Siren not sounding | Relay inverted | Check `inverted:` setting |
| DHT22 shows NaN | Wiring loose | Check data pin connection |
| False alarms | Threshold too low | Increase GAS_THRESHOLD |

## Wiring Diagram
See File 05, Section 6 for MQ-6 pinout
See project photos: /photos/node-b1-wiring.jpg

## Last Updated
2026-08-18 by [Your Name]
```
