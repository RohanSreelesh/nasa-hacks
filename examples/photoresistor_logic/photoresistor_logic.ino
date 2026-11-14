const float THRESHOLDLIGHT = 100;

const int PHOTORESISTOR_PIN = PA0;
const int LED_PIN  = PC13;

const int DARK  = HIGH;
const int LIGHT = LOW;

float photoresistor_reading;
int   lightCount = 0;    // light readings in a row

void setup()
{
   Serial.begin( 9600 );
   while( !Serial );

   pinMode( LED_PIN, OUTPUT );
   digitalWrite( LED_PIN, DARK );
   pinMode( PHOTORESISTOR_PIN, INPUT_ANALOG );
}

void loop()
{
   photoresistor_reading = analogRead( PHOTORESISTOR_PIN );
   Serial.println( photoresistor_reading );

   if( photoresistor_reading <= THRESHOLDLIGHT )
   {
      lightCount++;
      if( lightCount >= 100 )                // 10 s of light
      {
         digitalWrite( LED_PIN, LIGHT );
      }
   }
   else
   {
      lightCount = 0;
      digitalWrite( LED_PIN, DARK );
   }

   delay( 100 );
}
