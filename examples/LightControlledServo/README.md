# Light-controlled servo

Moves to a protected position in darkness and an exposed position in bright light. Starts protected and operates without Serial Monitor. A threshold band prevents repeated switching near the threshold. Opens after 500 ms of stable brightness and closes after 500 ms of stable darkness for quick testing.

## Wiring

- Photoresistor voltage-divider output: PA0 (0–3.3 V only). Keep your existing photoresistor divider wiring; a bare photoresistor alone does not produce a defined voltage reading.
- Servo signal: PA8.
- Servo positive: external supply within the actual servo's rating (the supplied listing specifies 4.8–6.0 V).
- Servo ground, external supply negative, and Blue Pill GND: all connected together.
- Blue Pill: USB powered; external supply positive stays disconnected from the board.

The measured 6.4 V AA pack exceeds the listed servo rating; use a suitable regulated supply. Incorrect shared-ground wiring caused the earlier servo failures and was corrected.

## Run and calibrate

Open `LightControlledServo.ino` in Arduino IDE with the same STM32F103C8 board/upload settings used for the working servo test. Upload, then view readings at 9600 baud. Compilation and physical integration of this example still need verification.

1. First test without a mechanical load. Motion is limited to a commanded 90-degree arc: `PROTECTED_ANGLE = 0` (left, dark) and `EXPOSED_ANGLE = 90` (center, bright). Physical direction depends on mounting; if left is the other direction, use 180 for the protected position and keep center at 90. Calibrate actual travel without hitting stops.
2. Measure bright and dark readings. Set `LIGHT_THRESHOLD` between them (100 is the starting value from the photoresistor logic example).
3. Set `BRIGHT_IS_LOWER` according to the measurements. It defaults to true to match the original example's comparison.
4. Set `HYSTERESIS` smaller than half the bright/dark reading difference. Readings must cross threshold ± this margin and stay there for the corresponding light/dark duration before the position changes.

The sensing photoresistor must still see ambient light while the mechanism is protected. If the servo covers the only light sensor completely, it cannot detect returning light and reopen. Keep that sensor exposed or use another exposed sensor to control reopening.
