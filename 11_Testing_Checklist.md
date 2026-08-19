# 11_Testing_Checklist.md
# SmartHome Prototype — Testing & Commissioning Checklist

**Version:** 1.0 | **Date:** August 2026

---

## Phase 1: Pre-Commissioning (Before Installing)

### Hub Testing
- [ ] Old PC boots reliably
- [ ] Ubuntu Server installed, static IP set
- [ ] Docker running, all containers start
- [ ] Home Assistant accessible at http://192.168.1.10:8123
- [ ] MQTT broker responding (test with mosquitto_pub/sub)
- [ ] Node-RED accessible and connected to HA
- [ ] WiFi coverage >-65 dBm on both floors
- [ ] Tailscale/Cloudflare remote access working
- [ ] Backup script created and tested

### Per-Node Bench Testing (Before Installation)
For EACH node:
- [ ] All sensors read reasonable values in Wokwi
- [ ] ESPHome YAML compiles without errors
- [ ] Node connects to WiFi
- [ ] Node appears in Home Assistant
- [ ] All entities visible in HA
- [ ] OTA update works
- [ ] Actuators (relays) click when toggled from HA
- [ ] Safety logic triggers correctly (simulate alarm conditions)
- [ ] Power consumption measured (should match expected)
- [ ] Enclosure fits all components
- [ ] Labels applied to all wires

---

## Phase 2: Installation Testing

### Electrical Safety (Before Power-On)
- [ ] Multimeter continuity test: No shorts on any circuit
- [ ] Fuse installed and correct rating
- [ ] Earth connection verified on all metal enclosures
- [ ] GFCI/ELCB installed and tested (press test button)
- [ ] Cable gauges appropriate for current
- [ ] No exposed conductors
- [ ] Enclosures properly closed
- [ ] Emergency cutoff accessible

### Node-by-Node Installation Check

**Kitchen Safety (CRITICAL):**
- [ ] MQ-6 positioned 30cm from floor (LPG)
- [ ] MQ-2 on ceiling
- [ ] Gas valve wiring double-checked
- [ ] Exhaust fan relay tested
- [ ] Simulate gas leak → Verify sequence: exhaust → valve → siren
- [ ] Simulate smoke → Verify siren + notification
- [ ] Simulate water leak → Verify valve closes
- [ ] Manual reset works

**Water Tank & Pump:**
- [ ] Float switches move freely
- [ ] Ultrasonic sensor aimed correctly at water surface
- [ ] Pump direction correct (pumps water, not air)
- [ ] Dry-run simulation: Pump stops automatically
- [ ] Auto-fill: Empty → Pump ON, Full → Pump OFF
- [ ] Sump low: Pump prevented from running

**Security System:**
- [ ] All reed switches respond to magnet
- [ ] PIR detects motion at expected range
- [ ] Entry delay: 30 seconds before siren
- [ ] Instant trigger: Window break → Immediate siren
- [ ] Disarm function works
- [ ] Siren audible throughout house

**Cameras:**
- [ ] Clear image day and night
- [ ] IR LEDs illuminate area
- [ ] Motion detection triggers recording
- [ ] SD card stores footage
- [ ] Stream accessible from HA dashboard

---

## Phase 3: System Integration Testing

### Communication
- [ ] All 15+ nodes online simultaneously
- [ ] MQTT messages flowing (check with mosquitto_sub -t "#")
- [ ] No WiFi disconnections over 24 hours
- [ ] Hub CPU usage <50% average
- [ ] Hub RAM usage <70%

### Automation Testing
- [ ] Morning scene activates correctly
- [ ] Night scene activates correctly
- [ ] Away mode arms security, turns off lights
- [ ] Motion lights: Walk through each room, verify timing
- [ ] Climate control: Temperature threshold triggers fan/AC
- [ ] Garden watering: Dry soil → Valve opens → Moisture rises → Valve closes
- [ ] Aquarium: Temperature maintains range, feeder operates

### Safety System End-to-End
- [ ] Gas leak → Phone notification within 5 seconds
- [ ] Smoke detected → Phone notification + siren
- [ ] Water leak → Valve closes + phone alert
- [ ] Panic button → Siren + phone alert
- [ ] Dry run → Pump stops + phone alert
- [ ] Power outage → Hub stays online (UPS), critical nodes on battery

### Stress Testing
- [ ] All nodes online for 72 hours continuous
- [ ] Simulate WiFi outage → Nodes reconnect automatically
- [ ] Simulate hub reboot → All nodes reconnect within 2 minutes
- [ ] Trigger 5 automations simultaneously → System responsive
- [ ] OTA update 3 nodes simultaneously → All succeed

---

## Phase 4: 30-Day Burn-In

### Daily Checks (First Week)
- [ ] All nodes online
- [ ] No false alarms
- [ ] Dashboard loads quickly
- [ ] Mobile notifications received
- [ ] Backup created successfully

### Weekly Checks (Weeks 2-4)
- [ ] Review logs for errors
- [ ] Check sensor drift (recalibrate if needed)
- [ ] Verify backup integrity
- [ ] Test emergency procedures with family
- [ ] Document any anomalies

### 30-Day Sign-Off Criteria
- [ ] Uptime: Hub >99%, nodes >98%
- [ ] False alarms: <2 per week
- [ ] No safety incidents
- [ ] Family comfortable using dashboard
- [ ] All documentation updated
- [ ] Ready for commercialization planning

---

*End of 11_Testing_Checklist.md*
