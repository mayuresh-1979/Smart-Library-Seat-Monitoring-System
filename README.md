Library Seat Availability Monitoring System
An IoT-based smart monitoring system developed using ESP32, IR Sensor, and FSR Sensor to detect real-time
library seat occupancy and display seat availability through LEDs and a WiFi-based web dashboard.

______________________________________________________________________________________________________________
Project Overview

This project solves the problem of finding vacant seats in libraries using:
• ESP32 DevKit V1
• IR Sensor
• FSR Sensor
• WiFi Dashboard
• LEDs
The ESP32 processes data from sensors and updates seat status in real-time.

_____________________________________________________________________________________________________________
Features

• Real-time seat occupancy detection

• WiFi-based web dashboard

• Dual sensor validation system

• LED indication

• Low-cost IoT implementation

• Scalable architecture

______________________________________________________________________________________________________________
Hardware Components:- 
• ESP32 DevKit V1
• IR Sensor Module
• FSR 402 Sensor
• Red LED
• Green LED
• 220Ω Resistors
• 10kΩ Resistor
• 0.1µF Capacitor
• 10µF Capacitor

_____________________________________________________________________________________________________________
ESP32 Pin Connections:- 

IR Sensor OUT -> GPIO4

FSR Sensor Output -> GPIO34

Red LED -> GPIO5

Green LED -> GPIO19

_____________________________________________________________________________________________________________
Working Principle
1. IR sensor detects user presence

2. FSR sensor detects pressure

3. ESP32 processes sensor data

4. LEDs indicate seat status

5. Web dashboard displays live occupancy

Seat is considered occupied only when:
• IR detects presence
AND
• FSR pressure exceeds threshold

____________________________________________________________________________________________________________
Dashboard
The ESP32 hosts a live web dashboard accessible through browser using local IP address.


Features:-

  • Live seat status

  • Real-time sensor values

  • Dynamic UI updates

  • WiFi-based monitoring

____________________________________________________________________________________________________________
Software:- 

  • Arduino IDE

  • ESP32 Board Package 2.0.17

  • Embedded C++

  • WebServer Library

____________________________________________________________________________________________________________
Future Scope:- 

  • Mobile app integration

  • Cloud database support

  • Seat reservation system

  • Multi-seat scalability

  • Analytics dashboard

___________________________________________________________________________________________________________
Team Members:-

  • Mayuresh Mudase

  • Isha Mishra

  • Parth Mishra
