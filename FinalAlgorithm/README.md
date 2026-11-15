# Final algorithm foundation

Open `FinalAlgorithm.ino` in Arduino IDE. States follow the supplied code photo, with `PROTECTING_PHOTORESISTOR` added after panel retraction and subsequent states renumbered. The initial state is `NOT_STARTED`.

Intended sequence: detect light from the opening door, wait for the door to open, drive down the ramp, deploy panels, detect the storm, retract panels, tilt the photoresistor into its protected position, wait out the storm, redeploy panels, finish.

`PROTECTING_PHOTORESISTOR` represents the sensor tilt after `RETRIEVING_SOLAR_PANELS_1` and before `WAITING_OUT_STORM`. Restoring the sensor and determining when the storm ends still need implementation; readings while tilted may differ from exposed readings.

Timing constants come from the challenge package, PDF page 4:

- Door opening: approximately 5 seconds.
- Lights dim: over 10 seconds.
- Sand starts: 15 seconds after the lights are fully off.
- Sand and fan: 45 seconds.
- Operation time after the storm: 2 minutes, including redeployment and any cleaning or movement before final measurement.

These are separate intervals, not timestamps measured from startup. The 15-second delay starts after dimming finishes; the 2-minute operation period starts when the storm ends.

## Hardware integration pending

This walkthrough uses only the photoresistor and onboard LED. Wheel driving, panel winding/unwinding, and sensor tilt/restoration are stubbed. One motor is planned for the wheels and another for the panel winder; wiring, pin assignments, and motor integration remain pending. The walkthrough does not require the SparkFun motor library.

## Onboard state indicator

`StateIndicator` uses the Blue Pill's onboard PC13 LED (LOW = on); no external LED is required. It flashes the main state number, then pauses for 1.5 seconds before repeating. Each flash is 200 ms on with 200 ms between flashes. A state change clears the old pattern and waits 1.5 seconds before displaying the new number.

| Blinks | State |
| --- | --- |
| 1 | NOT_STARTED |
| 2 | DOOR_OPENED |
| 3 | MOVING_DOWN_RAMP |
| 4 | DEPLOYING_SOLAR_PANELS_1 |
| 5 | WAITING_FOR_STORM |
| 6 | STORM_DETECTED |
| 7 | RETRIEVING_SOLAR_PANELS_1 |
| 8 | PROTECTING_PHOTORESISTOR |
| 9 | WAITING_OUT_STORM |
| 10 | STORM_OVER |
| 11 | DEPLOYING_SOLAR_PANELS_2 |
| 12 | DONE |

The main loop updates the indicator without `delay()`. The walkthrough waits for one full blink group before advancing each state. Future modules should leave PC13 to this indicator and avoid blocking the loop.

## Sensor-driven walkthrough

Upload `FinalAlgorithm.ino` with the photoresistor input connected to PA0 as in the existing sensor examples. No motors or servos are needed. Open Serial Monitor at **9600 baud** for state names/numbers printed once on entry; the sketch runs even without Serial Monitor.

1. Begin with the sensor covered. State 1 blinks while waiting for light.
2. Uncover it. State 2 waits at least 5 seconds for door opening, then simulated ramp travel and panel deployment advance to state 5.
3. At state 5, cover the sensor and keep it covered. Storm detection, panel retraction, and photoresistor protection advance to state 9.
4. At state 9, uncover the sensor. Storm-over and redeployment stages advance to state 12 (`DONE`). It stays there and repeats 12 flashes; reset the board to restart.

Each state must display at least one complete blink group before advancing, so the full route is visible. Sensor waits last as long as needed. Mechanical stages finish after their blink group; actual motion completion checks, the storm schedule, and the final 2-minute operation period are not enforced in this walkthrough. This visibility gating is for walkthrough testing and must be removed from time-critical hardware transitions later.

`LightSensor` reuses the existing threshold of 100, hysteresis of 15, lower-is-brighter polarity, and 500 ms stability check. These require calibration on the actual sensor. Leave the sensor exposed to ambient light during this walkthrough: restoring light simulates storm completion, and physical tilt/restoration is not implemented. This does not establish how the final tilted-sensor system will detect storm completion.
