# 🚗 Arduino CAN Bus Distance Telemetry & Monitoring System

An automotive-grade embedded telemetry prototype built with **Arduino Uno**, **MCP2515 CAN Bus Controller**, and an **HC-SR04 Ultrasonic Sensor**. 

The project demonstrates real-time sensor acquisition, CAN frame packing/broadcasting, and deterministic message processing via SPI communication. It features a standalone hardware validation workflow utilizing the MCP2515 internal **Loopback Mode** alongside traditional multi-node bus configurations.

---

## 📌 Features

- **Standard CAN 2.0A Protocol:** Operates at 500 kbps baud rate with custom message identifiers.
- **Hardware-in-the-Loop Loopback Validation:** Verifies SPI integrity, controller register configuration, and RX/TX FIFO buffers without requiring an external bus transceiver.
- **Modular Embedded Architecture:** Decoupled distance acquisition, CAN payload construction, and serial diagnostic interfaces.
- **Fail-Safe Controller Handshake:** Built-in verification for 8 MHz oscillator configurations and SPI state machine readiness.

---

## 🛠️ Hardware Requirements

| Component | Model / Spec | Quantity |
| :--- | :--- | :---: |
| Microcontroller | Arduino Uno R3 (ATmega328P) | 1 |
| CAN Controller & Transceiver | MCP2515 + TJA1050 (8 MHz Crystal) | 1 |
| Ultrasonic Sensor | HC-SR04 | 1 |
| Display | 1602 Character LCD (Parallel / I2C) | 1 |
| Power / Interconnect | Solderless Breadboard & Jumpers | - |

---

## 🔌 Hardware Wiring & Pinout

### 1. MCP2515 CAN Module (SPI Interface)
| MCP2515 Pin | Arduino Uno Pin | Function |
| :--- | :--- | :--- |
| **VCC** | **5V** | System Power |
| **GND** | **GND** | System Ground |
| **CS** | **D10** | SPI Chip Select |
| **SO (MISO)** | **D12** | SPI Master In Slave Out |
| **SI (MOSI)** | **D11** | SPI Master Out Slave In |
| **SCK** | **D13** | SPI Serial Clock |

### 2. HC-SR04 Ultrasonic Distance Sensor
| HC-SR04 Pin | Arduino Uno Pin | Function |
| :--- | :--- | :--- |
| **VCC** | **5V** | Power (Common Rail) |
| **Trig** | **D3** | Trigger Pulse Input |
| **Echo** | **D4** | Echo Timing Pulse Output |
| **GND** | **GND** | Ground (Common Rail) |

---

## 📡 CAN Message Structure

Distance telemetry is encoded in a lightweight standard 11-bit identifier frame:

+------------+-------------+-----------------------------+
| Field      | Value       | Description                 |
+------------+-------------+-----------------------------+
| Frame Type | Standard    | 11-bit Identifier           |
| CAN ID     | 0x101       | Distance Telemetry Stream   |
| DLC        | 1 Byte      | Payload length              |
| Data [0]   | 0x00 - 0xFF | Measured distance in cm     |
+------------+-------------+-----------------------------+

🚀 Getting Started
Prerequisites
Arduino IDE

MCP_CAN Library: Install mcp_can (by Cory J. Fowler) via Arduino Library Manager or clone directly:

git clone [https://github.com/coryjfowler/MCP_CAN_lib.git](https://github.com/coryjfowler/MCP_CAN_lib.git)

Flashing Firmware

1.Connect your Arduino Uno via USB.

2.Select your Board (Arduino Uno) and corresponding COM Port under Tools.

3.Open src/can_telemetry_loopback/can_telemetry_loopback.ino.

4.Verify oscillator settings match your hardware (default: MCP_8MHZ).

5.Click Upload and open the Serial Monitor at 9600 baud.
