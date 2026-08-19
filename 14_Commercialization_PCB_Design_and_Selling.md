# 14_Commercialization_PCB_Design_and_Selling.md
# SmartHome Prototype — Commercialization Roadmap

**Version:** 1.0 | **Date:** August 2026

---

## Phase 1: Prototype to PCB (Months 7-9)

### PCB Design in EasyEDA
1. **Create account:** easyeda.com
2. **Design 3 standard PCBs:**
   - **Sensor Node PCB:** ESP32 + 4x analog inputs + I2C + 2x relay + power
   - **Safety Node PCB:** ESP32 + gas/smoke inputs + 3x relay + buzzer
   - **Camera Node PCB:** ESP32-CAM + PIR + IR LED driver + 5V reg
3. **Design rules:**
   - 2-layer, 1.6mm thickness
   - Trace width: 1mm for power, 0.3mm for signals
   - Keep mains traces on one side, isolated from low voltage
   - Fuse holder on PCB
   - Mounting holes: 3.2mm diameter

### JLCPCB Ordering
1. Export Gerber from EasyEDA
2. Upload to jlcpcb.com
3. Select:
   - 2 layers, 1.6mm, HASL
   - Color: Green (cheapest) or Black (premium look)
   - Quantity: 10 sets (5 each type)
4. Cost: ~₹150-300 per PCB at 10 qty
5. Delivery: 7-15 days to India

### Enclosure Design
- **Option A:** Off-the-shelf IP65 ABS boxes (₹150-300)
- **Option B:** 3D printed (PETG/ABS) — design in Fusion 360
- **Option C:** Injection mold (₹50,000 tooling, viable at 500+ units)

---

## Phase 2: Branded Kit (Months 10-14)

### Product Tiers

| Tier | Name | Includes | Price |
|------|------|----------|-------|
| **Basic** | Smart Flat Lite | 8 nodes, hub software, 1-year support | ₹35,000 |
| **Standard** | Smart Flat Pro | 15 nodes, cameras, voice, 2-year support | ₹55,000 |
| **Premium** | Smart Flat Elite | 20 nodes, AI cameras, predictive maintenance, 3-year support | ₹75,000 |

### Packaging
- Branded box with foam cutouts
- Quick Start Guide (Hindi + English)
- Pre-flashed nodes labeled by room
- QR code linking to installation video
- Safety warning card

### Support Model
- **Installation:** DIY with video guide OR paid installation (₹5,000)
- **Support:** WhatsApp group + phone hotline
- **Warranty:** 1 year on electronics, 5 years on PCB

---

## Phase 3: Scaling (Months 15-24)

### Manufacturing Partnership
- Partner with local PCB assembly house (Bangalore/Delhi)
- Or set up small SMT line (₹5-10 lakh investment)
- Target: 50 units/month initially

### Sales Channels
- **Direct:** Website + Instagram/WhatsApp
- **B2B:** Builder partnerships (pre-install in new flats)
- **Retail:** Local electrical shops
- **Marketplace:** Amazon.in, Flipkart

### Marketing
- Real installation videos (before/after)
- Customer testimonials
- Cost comparison: "₹55,000 vs ₹2,00,000 for branded system"
- Energy savings calculator

---

## Legal & Compliance
- Register business: Sole proprietorship or LLP
- GST registration (mandatory above ₹20 lakh)
- BIS certification for mains-connected products (ISI mark)
- Liability insurance (recommended)
- Clear terms: DIY install vs professional install liability

---

*End of 14_Commercialization_PCB_Design_and_Selling.md*
