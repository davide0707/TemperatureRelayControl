# Temperature-based Relay Control System

![Temperature Relay Control](https://img.shields.io/badge/Temperature%20Control%20Relay-v1.0-green)

## Overview

This project allows you to control a relay based on temperature readings from a **DS18B20** sensor. When the temperature exceeds a set threshold, the relay is activated. When the temperature drops below the threshold minus a hysteresis value, the relay is deactivated. This is ideal for applications like **temperature regulation systems**, **heating/cooling control**, or **automated environmental monitoring**.

---

## Features

- 🌡 **DS18B20 Temperature Sensor**: Measures temperature in Celsius.
- ⚡ **Relay Control**: Automatically switches the relay on/off based on temperature.
- 🔄 **Hysteresis Logic**: Prevents rapid switching by introducing a temperature buffer.
- 💡 **LED Indicator**: Provides status feedback with a built-in LED.
- ⚠️ **Error Handling**: Automatically retries on invalid sensor readings.

---

## Hardware Components

- **DS18B20 Temperature Sensor**: [Link to product](https://www.adafruit.com/product/374)
- **Relay Module**: [Link to product](https://www.adafruit.com/product/3191)
- **LED**: Built-in to the board (or an external LED if desired)
- **Arduino Board** (e.g., Arduino Uno or Nano)

---


## Code Explanation

The system works by reading the temperature from the **DS18B20** sensor every minute. When the temperature exceeds the **activation threshold**, the relay is activated. It will remain on until the temperature falls below the **activation threshold** minus the **hysteresis** value, ensuring a stable state without rapid switching.

### Key Functions:

- **`manageTemperature()`**: Reads the temperature and checks if it exceeds the threshold.
- **`activateRelay()`**: Activates the relay by setting the corresponding pin high.
- **`deactivateRelay()`**: Deactivates the relay by setting the pin low.
- **`handleReadError()`**: Manages sensor reading errors, retrying up to a maximum number of times.

---

## Setup

1. Clone the repository:

    ```bash
    git clone https://github.com/davide0707/TemperatureRelayControl.git
    cd TemperatureRelayControl
    ```

2. Install the required libraries:
    - **OneWire**: For communication with the DS18B20 sensor.
    - **DallasTemperature**: For reading the temperature data from the sensor.

3. Upload the code to your Arduino board.

4. Connect the **DS18B20 sensor** and **relay module** to the specified pins in the code.

---

## Example of Output

- **Relay Activated**: When the temperature exceeds the defined threshold, the relay is turned on.
- **Relay Deactivated**: When the temperature drops below the threshold minus hysteresis, the relay turns off.

```bash
Current temperature: 42.5°C
Relay activated.
