# ESP32-WebServer-Control
Controlled esp32 via html page

Summary
This project utilizes an ESP32 microcontroller to create a web server that can control LEDs, read temperature and humidity data from a DHT22 sensor, and control a servo motor. The web interface allows users to interact with these components through a simple HTML page served by the ESP32.

Description
This project is an example of using an ESP32 microcontroller to set up a simple web server with the following functionalities:

LED Control:

The web server provides a web page where users can control two LEDs (green and red) connected to the ESP32.
Users can turn each LED on or off through buttons on the web page.
Temperature and Humidity Monitoring:

The ESP32 reads temperature and humidity data from a DHT22 sensor.
The current temperature (in °C) and humidity (in %) are displayed on the web page.
Servo Motor Control:

The web server allows users to set the angle of a servo motor connected to the ESP32.
Buttons on the web page let users set the servo angle to 0° (close) or 100° (open).
Hardware Required
ESP32 development board
DHT22 sensor
Two LEDs (green and red)
Servo motor
Resistors (appropriate values for LEDs)
Connecting wires
Breadboard (optional, for prototyping)
Software Required
Arduino IDE with ESP32 board support
Adafruit Unified Sensor library
DHT sensor library
ESP32Servo library
Setup Instructions
Hardware Connections:

Connect the DHT22 sensor data pin to GPIO 4 of the ESP32.
Connect the green LED to GPIO 12 and the red LED to GPIO 13, each with an appropriate resistor.
Connect the servo motor control wire to GPIO 5 of the ESP32.
Software Configuration:

Open the Arduino IDE and install the necessary libraries: Adafruit Unified Sensor, DHT, and ESP32Servo.
Set your Wi-Fi credentials in the ssid and password variables in the code.
Upload the code to your ESP32 board.
Accessing the Web Server:

Once the code is uploaded and the ESP32 is connected to Wi-Fi, open the Serial Monitor to find the IP address assigned to the ESP32.
Enter the IP address in a web browser to access the control interface.
