# Christmas lights
Using the ESP-32 as a controller 

## Requirements
* ESP-32
* LEDs (either single RGB LED, or LED strip)
* wires
* npn transistors
* ESP-IDF (with working components)

## Wiring
* Pins 5, 18, 19 are RED, GREEN and BLUE, respectively (high-active)
* If overall current exceeds the 40mA allowed by the GPIO pins, or higher than 5V is needed, then use transistors with their Base connected to the above mentioned pins. Otherwise (e.g. with a single LED) connect their positive ends to these pins.

For more info, look at the wiring sketches in the `wiring` folder!

## Usage
0. Clone the repo
1. Set the SSID and PASS definitions in `header.h` for an available network's name and password.
2. Plug in the ESP32 board / chip over a serial connection, then compile and flash (if your user can access serial ports without privilege escalation, omit the `sudo -E`):
```
    sudo -E make flash
```
3. Take note of its IP address (either via your Router's management page, or by looking through the output of the chip with a serial monitor).
4. Open that site in a browser.
5. In this page, the following settings are to be seen:

    * Red, Green, Blue - if you choose the manual mode, you can set the LED's colour here.
    * Brightness, alpha-speed, beta-speed, alpha, beta, speed - if you choose the auto mode, the program will follow a route on the surface of a sphere (brightness - radius; alpha, beta - starting parameters; alpha-speed, beta-speed - how big jumps should the program make from one colour to another; speed - overall speed of the transition). This sphere represents the entire possibility of colours on a given overall brightness, with its axes defined by the 3 colours - Red, Green, Blue.
    * Auto vs. Manual - to choose from the two types. 

6. Click submit, and see how the LEDs change!
