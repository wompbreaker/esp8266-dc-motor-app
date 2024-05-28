<!-- omit in toc -->
# Android app controlled ESP8266 DC motor
<!-- omit in toc -->
## A small scale IoT project written in C/C++ (for ESP8266 microcontroller) and Android Studio Java
Welcome to the Android App Controlled ESP8266 DC Motor project! This (IoT) project showcases how to control a DC motor connected to an ESP8266 microcontroller via an Android app. The ESP8266 connects to a WiFi network and responds to HTTP POST requests sent by the Android app to control the motor.
<!-- omit in toc -->
## Table of contents
- [Overview](#overview)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Setup and Installation](#setup-and-installation)
  - [ESP8266 Setup](#esp8266-setup)
  - [Android App Setup](#android-app-setup)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Overview
This project demonstrates how to control a DC motor using an ESP8266 microcontroller and an Android application. The ESP8266 is programmed to connect to a WiFi network and listen for HTTP POST requests. The Android app, written in Java, has two buttons that send these HTTP requests to the ESP8266 to control the motor.
## Hardware Requirements
- ESP8266 microcontroller
- DC motor
- Motor driver (e.g., L298N or similar)
- Power supply for the motor and ESP8266
- Connecting wires
- Breadboard (optional, for prototyping)
## Software Requirements
- Arduino IDE for programming the ESP8266
- Android Studio for building and running the Android app
## Setup and Installation
### ESP8266 Setup
1. Install Arduino IDE:\
   Download and install the [Arduino IDE](https://www.arduino.cc/en/software)
2. Install the necessary libraries for working with ESP8266
3. Connect the ESP8266
   - Wire the ESP8266 to your computer using a USB to TTL serial adapter.
   - Connect the DC motor to the motor driver and then to the ESP8266.
4. Upload the Arduino Code:
   - Make sure to modify the WiFi credentials
      ```c
      const char* SSID = "ssid";
      const char* PASSWORD = "password";
      ```
   - Set your IP address to an IP address that's currently not being used
      ```c
      IPAddress ip(192, 168, 1, 7);  // set ESP8266's IP Address
      IPAddress gateway(192, 168, 1, 1);
      IPAddress subnet(255, 255, 255, 0);
      IPAddress dns(192, 168, 1, 1);
      WiFi.config(ip, gateway, subnet, dns);
      ```
### Android App Setup
1. Install Android Studio:\
   Download and install [Android Studio](https://developer.android.com/studio).
2. Create a Project:
   - Import the provided Android project files in Android Studio.
   - Make sure you have the necessary SDKs and dependencies installed. (*This often becomes an issue so go to gradle and check if there are some dependencies that are deprecated*). 
3. Modify the App Code:
   - In the **ControlActivity.java** file, set the IP address of the ESP8266 to the IP address you set in **nodeMCU1.ino**.
      ```java
      String url = "192.168.1.7";  // ESP8266's IP Address
      ```
4. Build and Run the App:
   - Connect your Android device or use an emulator.
   - Build and run the app from Android Studio.
5. If there are any issues in the code, you can use `Log.d()` for debugging
## Usage
1. Power Up:
   - Make sure the ESP8266 and the motor driver are powered on.
   - The ESP8266 should connect to your WiFi network.
2. Control the Motor:
   - Open the Android app on your device.
   - Use the two buttons to send HTTP POST requests to the ESP8266 and control the motor.
## Contributing
Contributions are welcome! Please open an issue or submit a pull request for any improvements or bug fixes.
## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.