# Smart Fire Detection and Control Bot

## Overview
The Smart Fire Detection and Control Bot is an embedded robotic system designed to detect and suppress fire autonomously. It integrates flame sensing, real-time control, mobility, and a water-based extinguishing mechanism to minimize response time and reduce dependency on human intervention.

---

## Problem Statement
Conventional fire detection systems primarily provide alerts and rely on manual response. This delay in action increases the risk of fire spread, resulting in significant damage to life and property.

---

## Objective
- Detect fire at an early stage using flame sensors  
- Automate navigation toward the fire source  
- Implement an effective fire suppression mechanism  
- Reduce human exposure to hazardous environments  
- Develop a cost-effective and scalable solution  

---

## System Architecture

### Sensing Layer
- Three IR flame sensors detect infrared radiation emitted by fire  
- Provides directional input (Left, Center, Right)

### Control Layer
- Arduino UNO processes sensor data and executes control logic  

### Actuation Layer
- L298N motor driver controls robot movement  
- DC motors enable navigation  
- Servo motor aligns water nozzle  
- Relay-controlled pump performs fire suppression  

### Power System
- 12V battery supply  
- Regulated 5V for control circuitry  

---

## Components
- Arduino UNO  
- IR Flame Sensors (3 units)  
- L298N Motor Driver  
- DC Motors with Chassis  
- Servo Motor (SG90)  
- Water Pump with Pipe  
- Relay Module  
- 12V Battery  
- Jumper Wires  

---

## Working Principle
The system continuously monitors the environment using flame sensors. Upon detecting fire, the controller identifies its direction and navigates the robot toward the source. The servo aligns the nozzle, and the pump activates to extinguish the fire. The system then resumes monitoring.

---

## Applications
- Industrial and warehouse fire safety  
- Residential and office environments  
- Laboratory safety systems  
- Robotics and automation research  

---

## Advantages
- Reduced response time  
- Minimal human intervention  
- Cost-effective implementation  
- Portable and scalable design  

---

## Limitations
- Limited sensing range  
- Susceptible to false triggers from intense light sources  
- Dependent on continuous power supply  
- Not suitable for all fire classes  

---

## Future Enhancements
- Integration with IoT for remote monitoring  
- Multi-sensor fusion (smoke, gas, temperature)  
- AI-based fire detection using vision systems  
- Advanced extinguishing mechanisms  

---

## Team
- Alle Keerthi Harsha  
- Alluvada Mythri  
- Sodisetti Nikhita  
- Sreepangi Praneethi  

---

## Conclusion
This project presents a compact and efficient approach to automated fire detection and suppression. It demonstrates the application of embedded systems and robotics in improving safety and reducing risk in fire-prone environments.
