#include <Arduino.h>
#include "LightSensor.h"

namespace LightSensor {

const int PHOTORESISTOR_PIN = PA0;
const int THRESHOLDLIGHT = 100;
const int HYSTERESIS = 15;
const unsigned long STABLE_MS = 500;

bool ready = false;
bool light = false;
bool pending_light = false;
unsigned long pending_since = 0;

void setup()
{
  pinMode(PHOTORESISTOR_PIN, INPUT_ANALOG);
  ready = false;
  pending_light = analogRead(PHOTORESISTOR_PIN) <= THRESHOLDLIGHT;
  pending_since = millis();
}

void update()
{
  const int reading = analogRead(PHOTORESISTOR_PIN);
  bool requested_light = pending_light;
  if( reading < THRESHOLDLIGHT - HYSTERESIS )
    requested_light = true;
  else if( reading > THRESHOLDLIGHT + HYSTERESIS )
    requested_light = false;

  const unsigned long now = millis();
  if( requested_light != pending_light )
  {
    pending_light = requested_light;
    pending_since = now;
  }
  if( now - pending_since >= STABLE_MS )
  {
    light = pending_light;
    ready = true;
  }
}

bool isReady() { return ready; }
bool isLight() { return light; }

}
