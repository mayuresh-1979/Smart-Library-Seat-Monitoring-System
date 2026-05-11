📚 Library Seat Availability Monitoring System
An IoT-based smart monitoring system developed using ESP32, IR Sensor, and FSR Sensor to detect real-time library seat occupancy and display seat availability through LEDs and a WiFi-based web dashboard.

🚀 Project Overview
In libraries, students often waste time searching for vacant seats. Manual monitoring is inefficient and inaccurate. This project solves the problem using sensors and wireless communication.

The system continuously monitors whether a seat is:
✅ Available
❌ Occupied

The ESP32 processes data from:
IR Sensor (presence detection)
FSR Sensor (pressure detection)

The seat status is then:
Displayed using LEDs
Sent to a web dashboard through WiFi

This creates a smart, automated, and scalable library monitoring solution.

🎯 Objectives
Detect seat occupancy in real time
Reduce false detections using dual sensors
Display seat status visually
Enable remote monitoring using WiFi
Improve space utilization in libraries
Build a cost-effective IoT solution

⚙️ Features
✅ Real-time seat occupancy detection
✅ ESP32 WiFi-based monitoring
✅ Live web dashboard in browser
✅ Dual sensor validation system
✅ Red/Green LED indication
✅ Low-cost implementation
✅ Expandable for multiple seats
✅ Stable power design using capacitors

🧠 Working Principle
The system uses two sensors together for accurate occupancy detection.
1️⃣ IR Sensor
Detects whether a person is near the seat.

2️⃣ FSR Sensor
Detects pressure applied on the seat.

3️⃣ ESP32 Decision Logic
The seat is considered occupied only when:
IR sensor detects presence
AND
FSR detects pressure
This reduces false detection significantly.

FSR Connection using Voltage Divider Logic:
3.3V
  │
 [FSR]
  │
  ├────→ GPIO34
  │
 [10kΩ]
  │
 GND

Power Connections:
10µF Capacitor
Positive → 3V3
Negative → GND

0.1µF Capacitor
One side → 3V3
Other side → GND

These capacitors are used for: Voltage stabilization, Noise filtering and for preventing ESP32 resets during WiFi operation

Web Dashboard
The ESP32 hosts a live web dashboard accessible through browser.

Dashboard Features
Live seat status
Real-time FSR values
IR sensor status
Dynamic color indication
WiFi-based remote access

How to Access Dashboard?
After uploading code: Open Serial Monitor
                      Baud Rate = 115200
                      ESP32 prints IP address
                      Open Chrome and enter: http://192.168.x.x
                      Enter this IP in Chrome browser
                      The dashboard will open.

Why Two Sensors?
Using only IR sensor can cause: False detection
                                Environmental interference

Using only FSR can cause: Temporary pressure errors
Combining both improves accuracy significantly.

More details are provided in the Project Report.
