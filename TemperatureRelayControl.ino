######################################
######################################
# Copyright (c) 2024 Di Filippo Davide
######################################
######################################

#include <OneWire.h>
#include <DallasTemperature.h>

// Pin and parameters
const int tempSensorPin = 4;          // Pin of the DS18B20 temperature sensor
const int relayPin = 2;               // Pin of the relay
const int ledPin = 13;                // Pin of the built-in LED
const float activationTempThreshold = 40.0; // Temperature threshold for relay activation
const float hysteresis = 2.0;         // Hysteresis to avoid continuous relay on/off
const unsigned long intervalMillis = 60000; // Interval of 1 minute for temperature reading

// Sensor initialization
OneWire oneWire(tempSensorPin);
DallasTemperature sensors(&oneWire);

// State variables
bool relayActivated = false;          // Relay state
unsigned long previousMillis = 0;     // Time of the last reading
int invalidReads = 0;                 // Counter for invalid readings
const int maxInvalidReads = 5;        // Maximum number of failed readings

void setup() {
  Serial.begin(9600);  // Start serial communication
  delay(2000);         // Wait for 2 seconds for stabilization
  Serial.println("System started.");

  sensors.begin(); 
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);  
  relayActivated = false;
  pinMode(ledPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  // Check if it's time for a new reading
  if (currentMillis - previousMillis >= intervalMillis) {
    previousMillis = currentMillis; // Update the last reading time
    manageTemperature();
  }
}

// Function to manage temperature reading and relay logic
void manageTemperature() {
  sensors.requestTemperatures(); // Request temperature reading
  float temperature = sensors.getTempCByIndex(0); // Get temperature from the sensor

  // Check if the reading is valid (-127 is the standard error of DS18B20)
  if (temperature != -127.0) {
    invalidReads = 0;  // Reset the invalid reading counter
    Serial.print("Current temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    // Turn on the LED for half a second
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);

    // Relay activation logic
    if (!relayActivated && temperature >= activationTempThreshold) {
      activateRelay();
    } else if (relayActivated && temperature <= activationTempThreshold - hysteresis) {
      deactivateRelay();
    }
  } else {
    invalidReads++;
    handleReadError(); // Handle reading errors
  }
}

// Function to activate the relay
void activateRelay() {
  digitalWrite(relayPin, HIGH);
  relayActivated = true;
  Serial.println("Relay activated.");
}

// Function to deactivate the relay
void deactivateRelay() {
  digitalWrite(relayPin, LOW);
  relayActivated = false;
  Serial.println("Relay deactivated.");
}

// Function to handle reading errors
void handleReadError() {
  if (invalidReads < maxInvalidReads) {
    Serial.println("Error: invalid temperature reading, retrying...");
  } else {
    Serial.println("Error: too many invalid readings.");
    invalidReads = 0;  // Reset the counter to prevent blocking the program
  }
}
