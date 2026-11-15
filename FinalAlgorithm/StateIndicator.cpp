#include <Arduino.h>
#include "StateIndicator.h"

namespace StateIndicator {

const int LED_PIN = PC13;
const int DARK = HIGH;
const int LIGHT = LOW;
const unsigned long BLINK_MS = 200;
const unsigned long GROUP_PAUSE_MS = 1500;

int displayed_state = 0;
int blinks_completed = 0;
bool led_on = false;
bool pattern_shown = false;
unsigned long last_change = 0;
unsigned long wait_ms = GROUP_PAUSE_MS;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, DARK);
  displayed_state = 0;
  pattern_shown = false;
  blinks_completed = 0;
  led_on = false;
  last_change = millis();
  wait_ms = GROUP_PAUSE_MS;
}

void update(int state)
{
  const unsigned long now = millis();

  // Start a fresh blink group when the main state changes.
  if( state != displayed_state )
  {
    displayed_state = state;
    blinks_completed = 0;
    pattern_shown = false;
    led_on = false;
    digitalWrite(LED_PIN, DARK);
    last_change = now;
    wait_ms = GROUP_PAUSE_MS;
  }

  if( state <= 0 || now - last_change < wait_ms ) return;
  last_change = now;
  wait_ms = BLINK_MS;

  if( led_on )
  {
    digitalWrite(LED_PIN, DARK);
    led_on = false;
    ++blinks_completed;

    // All flashes are done: pause before repeating the group.
    if( blinks_completed == state )
    {
      pattern_shown = true;
      blinks_completed = 0;
      wait_ms = GROUP_PAUSE_MS;
    }
  }
  else
  {
    digitalWrite(LED_PIN, LIGHT);
    led_on = true;
  }
}

bool hasShownPattern()
{
  return pattern_shown;
}

}
