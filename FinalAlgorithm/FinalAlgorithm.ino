#include "StateIndicator.h"
#include "LightSensor.h"

const int NOT_STARTED = 1;
const int DOOR_OPENED = 2;
const int MOVING_DOWN_RAMP = 3;
const int DEPLOYING_SOLAR_PANELS_1 = 4;
const int WAITING_FOR_STORM = 5;
const int STORM_DETECTED = 6;
const int RETRIEVING_SOLAR_PANELS_1 = 7;
const int PROTECTING_PHOTORESISTOR = 8;
const int WAITING_OUT_STORM = 9;
const int STORM_OVER = 10;
const int DEPLOYING_SOLAR_PANELS_2 = 11;
const int DONE = 12;

int state = NOT_STARTED;
bool state_printed = false;
unsigned long state_started = 0;

const unsigned long DOOR_OPEN_TIME_MS = 5000;
const unsigned long LIGHT_DIM_TIME_MS = 10000;
const unsigned long SAND_START_DELAY_MS = 15000;
const unsigned long SANDSTORM_DURATION_MS = 45000;
const unsigned long POST_STORM_OPERATION_TIME_MS = 120000;

void setup() {
  Serial.begin(9600);
  LightSensor::setup();
  StateIndicator::setup();
  state_started = millis();
}

void loop() {
  LightSensor::update();
  StateIndicator::update(state);

  int next_state = state;
  switch( state )
  {
    case NOT_STARTED:
      if( !state_printed ) Serial.println("1: NOT_STARTED");
      if( !StateIndicator::hasShownPattern() ) break;
      if( LightSensor::isReady() && LightSensor::isLight() )
        next_state = DOOR_OPENED;
      break;
    case DOOR_OPENED:
      if( !state_printed ) Serial.println("2: DOOR_OPENED");
      if( !StateIndicator::hasShownPattern() ) break;
      if( millis() - state_started >= DOOR_OPEN_TIME_MS )
        next_state = MOVING_DOWN_RAMP;
      break;
    case MOVING_DOWN_RAMP:
      if( !state_printed ) Serial.println("3: MOVING_DOWN_RAMP");
      if( !StateIndicator::hasShownPattern() ) break;
      // TODO: drive only the wheel motor and wait for ramp exit.
      next_state = DEPLOYING_SOLAR_PANELS_1;
      break;
    case DEPLOYING_SOLAR_PANELS_1:
      if( !state_printed ) Serial.println("4: DEPLOYING_SOLAR_PANELS_1");
      if( !StateIndicator::hasShownPattern() ) break;
      // TODO: unfurl with the winder motor and wait for completion.
      next_state = WAITING_FOR_STORM;
      break;
    case WAITING_FOR_STORM:
      if( !state_printed ) Serial.println("5: WAITING_FOR_STORM");
      if( !StateIndicator::hasShownPattern() ) break;
      if( LightSensor::isReady() && !LightSensor::isLight() )
        next_state = STORM_DETECTED;
      break;
    case STORM_DETECTED:
      if( !state_printed ) Serial.println("6: STORM_DETECTED");
      if( !StateIndicator::hasShownPattern() ) break;
      next_state = RETRIEVING_SOLAR_PANELS_1;
      break;
    case RETRIEVING_SOLAR_PANELS_1:
      if( !state_printed ) Serial.println("7: RETRIEVING_SOLAR_PANELS_1");
      if( !StateIndicator::hasShownPattern() ) break;
      // TODO: furl with the winder motor and wait for completion.
      next_state = PROTECTING_PHOTORESISTOR;
      break;
    case PROTECTING_PHOTORESISTOR:
      if( !state_printed ) Serial.println("8: PROTECTING_PHOTORESISTOR");
      if( !StateIndicator::hasShownPattern() ) break;
      // TODO: tilt the sensor; leave it exposed during this walkthrough.
      next_state = WAITING_OUT_STORM;
      break;
    case WAITING_OUT_STORM:
      if( !state_printed ) Serial.println("9: WAITING_OUT_STORM");
      if( !StateIndicator::hasShownPattern() ) break;
      // Walkthrough input: restore light. Revisit when tilt is implemented.
      if( LightSensor::isReady() && LightSensor::isLight() )
        next_state = STORM_OVER;
      break;
    case STORM_OVER:
      if( !state_printed ) Serial.println("10: STORM_OVER");
      if( !StateIndicator::hasShownPattern() ) break;
      next_state = DEPLOYING_SOLAR_PANELS_2;
      break;
    case DEPLOYING_SOLAR_PANELS_2:
      if( !state_printed ) Serial.println("11: DEPLOYING_SOLAR_PANELS_2");
      if( !StateIndicator::hasShownPattern() ) break;
      // TODO: restore sensor and unfurl panels. Walkthrough skips 2-minute wait.
      next_state = DONE;
      break;
    case DONE:
      if( !state_printed ) Serial.println("12: DONE");
      if( !StateIndicator::hasShownPattern() ) break;
      break;
  }

  state_printed = true;

  if( next_state != state )
  {
    state = next_state;
    state_started = millis();
    StateIndicator::update(state);
    state_printed = false;
  }
}
