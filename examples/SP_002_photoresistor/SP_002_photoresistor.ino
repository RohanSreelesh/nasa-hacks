// -------- NEEDS CALIBRATION ---------------- 
// You must calibrate this for a given environment: 
// 1. Start in darkness, note the readings
// 2. Set the environment to whatever counts as "light", not the new readings
// 3. Then set this constant to a value between light and dark values
//    - Too low will detect light too early
//    - Too high will not detect light early enough
// 
const float THRESHOLD = 130.0; 
// 
// ------------------------------------------- 
 
const int PHOTORESISTOR_PIN = PA0; // Values from the photoresistor 
const int LED_PIN = PC13; // This lights up to signal something’s close 

const int DARK  = HIGH;
const int LIGHT = LOW;

float photoresistor_reading; 
int   signal_light_value; 
 
void setup()  
{ 
   Serial.begin( 9600 ); 
   while( !Serial ); 
 
   pinMode( LED_PIN, OUTPUT );     // Turn on led when it's "light"  
   digitalWrite( LED_PIN, DARK );  // Set dark to start 
 
   pinMode( PHOTORESISTOR_PIN, INPUT );     // Turn the signaling light off 
   photoresistor_reading = 0;
} 
 
void loop() 
{ 
   photoresistor_reading = analogRead( PHOTORESISTOR_PIN ); 
   Serial.print( "PHOTO TEST v2 | reading=" );
   Serial.println( photoresistor_reading );
   delay(500); // Two readings per second for easy upload verification 
 
   if( photoresistor_reading <= THRESHOLD )
   { 
     digitalWrite( LED_PIN, LIGHT ); 
   }
   else
   {
     digitalWrite( LED_PIN, DARK ); 
   }
} 
