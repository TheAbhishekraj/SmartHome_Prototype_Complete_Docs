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
- [ ] **48-Hour Breadboard Bench Burn-In completed:** Run the assembled circuit continuously on the bench prior to soldering. Verify voltage regulator temperatures (must stay <55°C) and check logs for unexpected ESP32 reboot loops or sensor timeouts due to marginal power quality.
- [ ] **Sensor Calibration:** Gas and smoke sensors (MQ-6, MQ-2) must be calibrated according to the calibration procedure below to prevent false alarms and ensure trigger reliability.

---

## Bench Burn-in & Sensor Calibration Procedures (CRITICAL)

### 1. 48-Hour Breadboard Bench Burn-in Procedure
Before committing components to a soldered protoboard or custom PCB:
1. **Setup:** Assemble the circuit on a breadboard. Connect all sensors, relays, status LEDs, and pull-up/down resistors.
2. **Firmware:** Flash the target ESPHome configuration. Configure logging step to `DEBUG` or `VERY_VERBOSE`.
3. **Mains Simulation:** Power the ESP32 via down-converted DC rails (not USB computer power) using the exact power supply (such as the ATX PSU or 5V/12V SMPS) specified for that node's placement.
4. **Thermal Monitoring:** Every 12 hours, measure the temps of:
   - Buck converter or linear voltage regulator (e.g. LM7805 or ASM1117).
   - The ESP32 shield area.
   - Any driver chips (A4988, motor bridges).
   *If any part registers >55°C (too hot to touch for >3 seconds), add a passive heatsink or step down the supply voltage.*
5. **Log Scrutiny:** Let it run for 48 hours. Connect via toolchain terminal/serial monitor or HA logs, and check for:
   - WiFi connection flapping (frequent disconnects/reconnects).
   - ESPHome watchdog boot triggers (e.g., `Reset reason: TG0_WDT_SYS_RESET` or `SW_CPU_RESET`).
   - Sudden reading spikes from DHT22 or Analog lines.

### 2. Gas Sensor (MQ-6/MQ-2) Calibration Protocol
MQ-series gas sensors use a heater coil to warm up a tin-dioxide ($SnO_2$) semiconductor layer. They require strict prep prior to deployment.
* **Pre-heating Burn-In (Required for new sensors):** Connect the sensor to its 5V VCC supply and let it run continuously for **48 hours** in clean air. The heater resistor must burn off factory coating impurities. The output will stabilize only after this period.
* **Baseline Zeroing ($R_0$ Calibration):**
  1. Move the warmed sensor to an outdoor or clean indoor air environment (fresh air baseline where gas concentration is assumed to be 0 ppm).
  2. Measure the sensor output resistance $R_s$. In ESPHome, monitor the raw resistance or voltage.
  3. Divide $R_s$ by the clean-air constant to compute $R_0$ (refer to sensor datasheet curves. For MQ-6, clean air ratio $R_s/R_0 \approx 10.0$; therefore $R_0 = R_{s(\text{clean})} / 10.0$).
  4. Write this custom $R_0$ value into the sensor block of your ESPHome YAML:
     ```yaml
     sensor:
       - platform: mq3            # Standard base for MQ-6/MQ-2 in ESPHome
         # ... other configs
         r0: 12400                # Set your calibrated R0 value in ohms
     ```
* **Functional Test (Tracer Gas Validation):**
  1. Once configured, place the node inside a plastic box/jar.
  2. Release a brief (0.5 second) unlit burst of gas from a standard utility/cigarette butane lighter near the sensor.
  3. Verify that the raw voltage reading climbs rapidly, the computed ppm rises over the trigger threshold (configured at ~10% of the Lower Explosive Limit / LEL), and the safety action sequence (solenoid closes, exhaust restarts, buzzer sounds) activates within <2 seconds.
  4. Verify the system latches its alarm state and requires manual HA dashboard intervention to reset the safety solenoid valve.

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
