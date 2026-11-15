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

const unsigned long DOOR_OPEN_TIME_MS = 5000UL;
const unsigned long LIGHT_DIM_TIME_MS = 10000UL;
const unsigned long SAND_START_DELAY_MS = 15000UL;
const unsigned long SANDSTORM_DURATION_MS = 45000UL;
const unsigned long POST_STORM_OPERATION_TIME_MS = 120000UL;

void setup() {
}

void loop() {
}
