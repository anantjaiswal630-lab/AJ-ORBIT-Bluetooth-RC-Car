Arduino Uno Bluetooth-controlled 4WD RC car using an L293D motor driver shield, with adjustable speed and wireless control.
# AJ-ORBIT Bluetooth-Controlled RC Car

<p align="center">
  <img src="https://github.com/user-attachments/assets/24b7d585-2401-44a4-8ae9-523bb19570dd" alt="AJ-ORBIT Logo" width="160">
</p>

<p align="center">
  <strong>Bluetooth-Enabled Four-Wheel Robotic Vehicle</strong><br>
  <em>Engineered under the AJ-ORBIT Robotics & Hardware Initiative</em>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Platform-Arduino%20Uno%20R3-00979D?style=for-the-badge&logo=arduino&logoColor=white" alt="Arduino Uno">
  <img src="https://img.shields.io/badge/Control-Bluetooth-7B2CBF?style=for-the-badge&logo=bluetooth&logoColor=white" alt="Bluetooth">
  <img src="https://img.shields.io/badge/Driver-L293D%20Shield-8B0000?style=for-the-badge" alt="L293D Motor Shield">
  <img src="https://img.shields.io/badge/Firmware-Arduino%20C%2B%2B-000000?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="Arduino C++">
</p>

---

## 📌 Project Overview

The **AJ-ORBIT Bluetooth RC Car** is a four-wheel robotic vehicle prototype designed for wireless motion control, embedded programming education, and practical robotics experimentation.

Built around an **Arduino Uno R3** and a compatible **L293D four-motor driver shield**, the system receives movement commands from a Bluetooth-enabled controller application. The onboard firmware interprets each command and controls motor direction and speed to produce forward, reverse, turning, and diagonal movement.

The project demonstrates the integration of microcontroller programming, wireless serial communication, motor-driver control, and differential-drive principles.

> **Hardware compatibility:** The firmware must match the exact motor shield installed. The `AFMotor` version of the code is intended for compatible Adafruit Motor Shield V1-style hardware, not every L293D shield.

---

## ⚙️ Working Principle & System Architecture

```text
       +------------------------------------------+
       |          Smartphone Controller           |
       |     Direction Commands / Speed Levels    |
       +------------------------------------------+
                          |
                  Bluetooth Serial Link
                          |
                          v
       +------------------------------------------+
       |          HC-05 / HC-06 Module             |
       |          UART Communication              |
       +------------------------------------------+
                          |
                          v
       +------------------------------------------+
       |             Arduino Uno R3               |
       |------------------------------------------|
       |  - Command Interpretation                |
       |  - Movement State Selection              |
       |  - Motor Speed Configuration              |
       |  - Communication Timeout Stop             |
       +------------------------------------------+
                          |
                 Direction / PWM Control
                          |
                          v
       +------------------------------------------+
       |       Compatible L293D Motor Shield       |
       |           Four Motor Channels             |
       +------------------------------------------+
               |        |        |        |
               v        v        v        v
             [M1]     [M2]     [M3]     [M4]
               |        |        |        |
               +--------+        +--------+
               Left Side         Right Side
```

### Control sequence

1. The user selects a movement command in the Bluetooth controller application.
2. The Bluetooth module sends the command to the Arduino.
3. The firmware decodes the character and selects the required movement.
4. The motor shield applies the direction and speed settings to the motors.
5. A communication timeout can stop the motors when commands are no longer received.

---

## ✨ Key Features

- **Wireless operation:** Bluetooth serial communication with a compatible smartphone app.
- **Four-wheel drive:** Controls four motors through a compatible motor shield.
- **Multi-directional movement:** Forward, reverse, left, right, and diagonal commands.
- **Adjustable speed:** Ten numbered speed levels plus a maximum-speed command.
- **Communication timeout:** Stops the motors if no command arrives within the configured interval.
- **Modular firmware:** Movement and motor-control functions are separated for easier modification.
- **Educational engineering:** Demonstrates embedded C++, serial communication, and DC motor control.

---

## 🧰 Hardware Requirements

| Component | Quantity | Function |
|---|---:|---|
| Arduino Uno R3 | 1 | Main microcontroller |
| Compatible L293D four-motor shield | 1 | Motor direction and speed control |
| HC-05 or HC-06 Bluetooth module | 1 | Wireless serial communication |
| DC geared motors | 4 | Vehicle propulsion |
| Four-wheel chassis | 1 | Mechanical structure |
| Wheels | 4 | Traction and movement |
| Suitable battery pack and holder | 1 | Motor power supply |
| Power switch | 1 | Power isolation |
| Jumper wires | As required | Signal connections |
| USB cable | 1 | Firmware upload |

**Electrical compatibility:** Verify the motor voltage, startup/stall current, shield rating, battery specifications, and Bluetooth logic levels before assembly. Four motors can exceed the current capability of some L293D shields.

---

## 💻 Software & Dependencies

- Arduino IDE
- Arduino Uno board support
- Compatible `AFMotor` library, if using V1-style shield hardware
- Bluetooth controller app that transmits the supported command characters

### Library installation

For compatible V1-style shields, install the library from the official repository:

**[Adafruit Motor Shield V1 Library](https://github.com/adafruit/Adafruit-Motor-Shield-library)**

1. Open the repository.
2. Download the ZIP archive.
3. In Arduino IDE, select **Sketch → Include Library → Add .ZIP Library**.
4. Select the downloaded archive.
5. Open the project `.ino` file and compile it.

The library is a separate dependency; it is not embedded inside the Arduino sketch.

---

## 🎮 Bluetooth Command Protocol

| Command | Operation |
|---|---|
| `F` | Move forward |
| `B` | Move backward |
| `L` | Turn left |
| `R` | Turn right |
| `G` | Forward-left movement |
| `I` | Forward-right movement |
| `H` | Backward-left movement |
| `J` | Backward-right movement |
| `S` | Stop all motors |
| `0`–`9` | Select a speed level |
| `q` | Set maximum speed |

The controller app must transmit the exact characters expected by the firmware.

**Timeout behaviour:** The supplied firmware uses a one-second command timeout. Continuous movement therefore requires repeated movement commands while a control button is held. If the app sends only one command per press, the vehicle will stop after the timeout.

---

## 🔌 Wiring & Assembly

For a compatible V1-style motor shield:

- Install the motor shield onto the Arduino Uno.
- Connect the left-side motors to M1 and M2.
- Connect the right-side motors to M3 and M4.
- Connect the Bluetooth module to the serial pins configured in the sketch.
- Follow the shield's printed power-terminal labels and power requirements.

For the version using `SoftwareSerial bluetooth(14, 15)`, the Arduino Uno's analog pins A0 and A1 serve as the Bluetooth RX and TX pins respectively:

| Bluetooth module | Arduino Uno |
|---|---|
| TXD | A0 (Arduino RX) |
| RXD | A1 (Arduino TX), through suitable voltage-level protection |
| GND | GND |
| VCC | Supply appropriate to the specific module |

Check the actual shield design before using these connections. Other shields may use different pins or require another library.

---

## 🚀 Getting Started

1. Clone or download this repository.
2. Install Arduino IDE and the correct board support.
3. Install the motor shield library required by your hardware.
4. Open `AJ_ORBIT_Bluetooth_RC_Car.ino`.
5. Select **Arduino Uno** and the appropriate serial port.
6. Compile and upload with motor power disconnected.
7. Connect the battery and pair the Bluetooth module with your controller.
8. Test each command with the wheels lifted before operating the vehicle on the floor.

---

## 📁 Repository Structure

```text
AJ-ORBIT-Bluetooth-RC-Car/
├── AJ_ORBIT_Bluetooth_RC_Car.ino
├── README.md
├── circuit-diagram.png
├── AJ_ORBIT_Bluetooth_RC_Car_Components.pdf
└── LICENSE
```

Add each file to the repository when it is available. Ensure the wiring diagram matches the actual shield and firmware.

---

## 🛡️ Safety & Engineering Notes

- Disconnect power before modifying wiring.
- Do not power the motors from the Arduino Uno's 5 V pin.
- Use a motor supply suitable for the motors and driver.
- Check the driver's per-channel and total-current limits.
- Keep fingers clear of wheels and gears during testing.
- Test the stop command and communication timeout before normal operation.
- Do not assume every L293D shield supports the `AFMotor` library.

---

## 🔭 Future Improvements

- Rechargeable battery monitoring
- Front-facing obstacle detection
- Headlights and status indicators
- A custom smartphone controller interface
- Telemetry and diagnostic feedback
- A documented, hardware-specific wiring harness

---

## 👨‍💻 Project Identity

**Brand:** AJ-ORBIT  
**Project:** Bluetooth-Controlled RC Car  
**Domain:** Robotics, Embedded Systems & Hardware Engineering  
**Tagline:** Build Beyond Limits.

---

## 📄 License

Choose an open-source license before distributing the project. The MIT License is one option for permitting reuse and modification of the code under its terms. Include a `LICENSE` file only after selecting the license.

<p align="center">
  <strong>AJ-ORBIT</strong><br>
  <em>Build Beyond Limits.</em>
</p>
