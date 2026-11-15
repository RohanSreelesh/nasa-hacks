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

Only constants and the initial state are implemented. `setup()` and `loop()` are empty. Pins, sensor thresholds, motor/servo controls, ramp travel time, photoresistor tilt, and state transitions still need implementation and calibration.
