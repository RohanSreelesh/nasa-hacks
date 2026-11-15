# Final algorithm foundation

Open `FinalAlgorithm.ino` in Arduino IDE. State names and values match the supplied code photo; the initial state is `NOT_STARTED`.

Intended sequence: detect light from the opening door, wait for the door to open, drive down the ramp, deploy panels, detect the storm, retract panels, wait out the storm, redeploy panels, finish.

Timing constants come from the challenge package, PDF page 4:

- Door opening: approximately 5 seconds.
- Lights dim: over 10 seconds.
- Sand starts: 15 seconds after the lights are fully off.
- Sand and fan: 45 seconds.
- Operation time after the storm: 2 minutes, including redeployment and any cleaning or movement before final measurement.

These are separate intervals, not timestamps measured from startup. The 15-second delay starts after dimming finishes; the 2-minute operation period starts when the storm ends.

Only constants and the initial state are implemented. `setup()` and `loop()` are empty. Pins, sensor thresholds, motor/servo controls, ramp travel time, photoresistor tilt, and state transitions still need implementation and calibration.
