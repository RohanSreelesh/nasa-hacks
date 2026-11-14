#include <Servo.h>

const int SENSOR_PIN = PA0;
const int SERVO_PIN = PA8;
const int MIN_PULSE = 600;
const int MAX_PULSE = 2300;

// Calibrate these with the mechanism disconnected first.
const int PROTECTED_ANGLE = 10;
const int EXPOSED_ANGLE = 170;
const int LIGHT_THRESHOLD = 100;
const int HYSTERESIS = 15;
// Original photoresistor example treats lower readings as brighter.
// Set false if your measured readings increase in bright light.
const bool BRIGHT_IS_LOWER = true;

Servo panelServo;
bool protectedState = true;
bool pendingState = true;
unsigned long pendingSince = 0;
const unsigned long DARK_STABLE_MS = 500;
const unsigned long LIGHT_STABLE_MS = 10000;

void setup() {
  Serial.begin(9600);
  // Do not wait for Serial: the mechanism must work without a computer.
  pinMode(SENSOR_PIN, INPUT_ANALOG);
  panelServo.attach(SERVO_PIN, MIN_PULSE, MAX_PULSE);
  panelServo.write(PROTECTED_ANGLE);
}

void loop() {
  const int reading = analogRead(SENSOR_PIN);
  bool requestedState = protectedState;

  // Keep the current position inside the threshold band.
  if (reading < LIGHT_THRESHOLD - HYSTERESIS) {
    requestedState = !BRIGHT_IS_LOWER;
  } else if (reading > LIGHT_THRESHOLD + HYSTERESIS) {
    requestedState = BRIGHT_IS_LOWER;
  }

  const unsigned long now = millis();
  if (requestedState != pendingState) {
    pendingState = requestedState;
    pendingSince = now;
  }
  const unsigned long stableTime = pendingState ? DARK_STABLE_MS : LIGHT_STABLE_MS;
  if (pendingState != protectedState && now - pendingSince >= stableTime) {
    protectedState = pendingState;
    panelServo.write(protectedState ? PROTECTED_ANGLE : EXPOSED_ANGLE);
  }

  if (Serial) {
    Serial.print("Light reading: ");
    Serial.print(reading);
    Serial.print(" | Position: ");
    Serial.println(protectedState ? "PROTECTED" : "EXPOSED");
  }
  delay(100);
}
