# Arduino ESP8266 IoT Home Appliance Control System

This project creates an IoT system using an ESP8266 (e.g., NodeMCU) to control home appliances remotely via a web interface, accessible worldwide using Pusher Channels for real-time communication.

## Overview
This system allows you to control up to four home appliances (e.g., lights, fans) remotely using an ESP8266 microcontroller connected to relay modules. The web interface, hosted as a single HTML file, communicates with the ESP8266 via Pusher Channels, enabling global access over the internet.

## Features
- Control appliances (ON/OFF) from anywhere in the world with an internet connection.
- Real-time communication using WebSockets via Pusher Channels.
- Simple web-based UI with buttons for each relay.
- Uses ESP8266 for Wi-Fi connectivity and relay control, eliminating the need for an Arduino.

## Hardware Requirements
- **ESP8266 Module**: NodeMCU (recommended) or ESP-01
- **Relay Module**: 4-channel, 5V, active-low relay module
- **Home Appliances**: Low-power devices (e.g., LED lights, small fans) for testing
- **Jumper Wires**: For connecting components
- **Power Supply**: 5V USB for NodeMCU
- **Wi-Fi Network**: With internet access for global connectivity

## Software Requirements
- **Arduino IDE**: For programming the ESP8266
  - Install ESP8266 board support (`http://arduino.esp8266.com/stable/package_esp8266com_index.json`)
  - Libraries: `ESP8266WiFi`, `WebSocketsClient`
- **Pusher Channels Account**: Free tier available at [pusher.com](https://pusher.com)
- **Web Browser**: For accessing the HTML interface

## Setup Instructions

### 1. Hardware Setup
- Connect the relay module to the NodeMCU:
  - **VIN** → Relay VCC (5V from USB)
  - **GND** → Relay GND
  - **D1 (GPIO 5)** → Relay IN1
  - **D2 (GPIO 4)** → Relay IN2
  - **D3 (GPIO 0)** → Relay IN3
  - **D4 (GPIO 2)** → Relay IN4
- Connect appliances to the relay’s NO (Normally Open) and COM (Common) terminals, ensuring a separate power source (e.g., 220V AC) for high-voltage appliances.
- Power the NodeMCU via USB.

### 2. Software Setup
#### a. Create a Pusher Channels App
- Sign up at [pusher.com](https://pusher.com) and create a new app (e.g., “HomeControl”).
- Note your Pusher credentials from the dashboard:
  - App ID (e.g., `1946828`)
  - Key (e.g., `c2fb34fa880960a9e301`)
  - Secret (e.g., `14edbc135cc73dae09ea`)
  - Cluster (e.g., `ap2` for Asia Pacific, Mumbai)

#### b. Program the ESP8266
- Install the required libraries in Arduino IDE:
  - `ESP8266WiFi`
  - `WebSocketsClient`
- Open the `ESP8266_IoT_Control.ino` file (or copy the code from this repository) and update:
  - Wi-Fi credentials (`ssid`, `password`)
  - Pusher credentials (`PUSHER_KEY`, `PUSHER_CLUSTER`)
- Select “NodeMCU 1.0” as the board and upload the code to the ESP8266.

#### c. Host the Web Interface
- Save the `index.html` file provided in this repository.
- Open it in a web browser locally, or host it on a static site (e.g., GitHub Pages) for global access.
- Update the HTML file with your Pusher credentials (Key, App ID, Secret, Cluster).

### 3. Testing
- Power on the NodeMCU and check the Serial Monitor (115200 baud) for Wi-Fi and Pusher connection status.
- Open `index.html` in a browser from any internet-connected device.
- Click the “ON” and “OFF” buttons to control the relays, and verify appliance responses in the Serial Monitor.

## Usage
- Access the web interface by opening `index.html` or its hosted URL.
- Use the buttons to toggle each relay (1–4) ON or OFF.
- The system uses Pusher Channels for real-time communication, allowing control from anywhere with internet access.

## Troubleshooting
- **ESP8266 Not Connecting to Wi-Fi**: Check Wi-Fi credentials and network signal.
- **Pusher Connection Issues**: Verify Pusher credentials, ensure internet access, and check for firewall restrictions on port 80.
- **HTML Interface Not Working**: Ensure Pusher credentials are correct, the browser has internet access, and no ad blockers interfere with WebSocket or API requests.
- **Relay Not Responding**: Verify hardware connections, relay logic (active-low), and appliance power supply.

## Contributing
Feel free to fork this repository, make improvements, and submit pull requests. Issues and suggestions are welcome!

## License
This project is open-source and available under the MIT License. See the LICENSE file for details (if applicable).

## Contact
- **Author**: Dr Neelesh Rajput
- **Email**: rajputneelesh55@gmail.com
- **GitHub**: https://github.com/Neeleshrajput55

---