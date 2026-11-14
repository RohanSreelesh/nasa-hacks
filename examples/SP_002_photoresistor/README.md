# Photoresistor example

Original sketch copied unchanged from `SP_002_photoresistor` for the hardware challenge.

1. Open `SP_002_photoresistor.ino` in Arduino IDE.
2. Select your STM32F103C8T6 / Blue Pill board and the upload method matching your hardware setup. This sketch uses STM32 pin names and is not configured for an Arduino Uno.
3. The sketch reads the photoresistor circuit on `PA0` and controls the onboard LED on `PC13` (active low). Keep the analog input within 0–3.3 V.
4. Upload, then open Serial Monitor at **9600 baud**. The sketch waits for the serial connection in `setup()` before reading the sensor.
5. Observe readings in darkness and in the intended light condition. Set `THRESHOLD` between those readings, then upload again. The current code turns the LED on when the reading is **at or below** the threshold; confirm that your sensor circuit produces lower readings in light.

The initial threshold is `130.0` and needs calibration. Board support, upload configuration, and wiring must match the physical hardware. This example has not yet been compiled or tested on the rover hardware.
