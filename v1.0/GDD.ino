// This #include statement was automatically added by the Particle IDE.
#include <OneWire.h>
//#include <DS18B20.h>
#include <ThingSpeak.h>
#include "DS18.h"

TCPClient client;
DS18 sensor(D13);

// ThingSpeak Channel Number and API Key
// **Should change this to be more secure
unsigned long myChannelNumber = XXXXX;	// change this to your channel number
const char * myWriteAPIKey = "XXXXXXXXXXXXXXXX"; // ThingSpeak channel write API key
const char * myReadAPIKey = "XXXXXXXXXXXXXXXX"; // ThingSpeak channel read API key
float low_temp = 100.0;
float high_temp = 0.0;
int day = 0;
float GDD = 0.0;

void setup() {
  // Section for Dallas-1-Wire for DS18
  Serial.begin(9600);
  // Set up 'power' pins, comment out if not used!
  pinMode(D3, OUTPUT);
  pinMode(D5, OUTPUT);
  digitalWrite(D3, LOW);
  digitalWrite(D5, HIGH);
  
  // Wait for time, 60 seconds, to be synchronized with Particle Device Cloud (requires active connection)
  waitFor(Time.isValid, 60000);
  
  // setup for daily wipe of high and low temps
  if (Time.isAM()){
    day = 0;
  } else {
      day = 1;
    }
  Particle.publish("AM-0 or PM-1: ", String(day), PRIVATE);
  
  
  //Section for MATLAB ThingSpeak
  ThingSpeak.begin(client);
  waitFor(Time.isValid, 10000);
  
  //Re establish high and low temps & GDDs on a new version of code/update/reboot
  low_temp = ThingSpeak.readFloatField(myChannelNumber, 1, myReadAPIKey);
  high_temp = ThingSpeak.readFloatField(myChannelNumber, 2, myReadAPIKey);
  GDD = ThingSpeak.readFloatField(myChannelNumber, 7, myReadAPIKey);
  if (low_temp != 100)
    Particle.publish("Found an old low temp", String(low_temp),PRIVATE);
  if (high_temp != 0)
    Particle.publish("Found an old high temp", String(high_temp),PRIVATE);


}

void loop() {
    
// Read the next available 1-Wire temperature sensor
  if (sensor.read()) {
      
    // Check the time
    //Time.format(Time.now(), "Now it's %I:%M%p.");
    //Particle.publish("Time now is", String(Time.now()), PRIVATE);
    //Particle.publish("Time day is", String(Time.day()), PRIVATE);
    
    // Check for change of day
    // PM -> day = 1
    // AM -> day = 0
    if (Time.isAM() && day == 1){
        day = 0;
        GDD += ((low_temp+high_temp)/2 - 50);
        ThingSpeak.writeField(myChannelNumber, 7, GDD, myWriteAPIKey);
        low_temp = 100.0;
        high_temp = 0.0;
    }
    if (Time.isPM() && day == 0){
        day = 1;
    }

    // time is 1553455218
    // time is 3/24/19 at 2:20:18 pm
    
    // Check if temp is how high or new low for GDD calculation
    if (sensor.fahrenheit() < low_temp){
        low_temp = sensor.fahrenheit();
        Particle.publish("New low temperature in F", String(sensor.fahrenheit()), PRIVATE);
        ThingSpeak.writeField(myChannelNumber, 1, low_temp, myWriteAPIKey);

    } else if (sensor.fahrenheit() > high_temp){
        high_temp = sensor.fahrenheit();
        Particle.publish("New high temperature in F", String(sensor.fahrenheit()), PRIVATE);
        ThingSpeak.writeField(myChannelNumber, 2, high_temp, myWriteAPIKey);

    } else {
        Serial.printf("No change in Temp");
        Particle.publish("No change in Temp");
    }
    // ThingSpeak will only accept updates every 15 seconds.
	// Delay of 60 seconds
	delay(60000); 
    // Do something cool with the temperature
    //Serial.printf("Temperature %.2f C %.2f F ", sensor.celsius(), sensor.fahrenheit());
    //Particle.publish("temperature in C", String(sensor.celsius()), PRIVATE);

	// Read the input on analog pins 1, 2 and 3:
	//float sensorValueRowX = sensor.fahrenheit();
    //float sensorValueRowY = analogRead(A2);
    //float sensorValueRowZ = analogRead(A3);
	
	// Set fields one at a time & then write them all at once - May need to change for each station
	// Should the same code be written across devices OR unique field numbders for each station?
	// Dallas - 1-wire can get individual thermometer IDs
    //ThingSpeak.setField(1,sensorValueRowX);
    //ThingSpeak.setField(2,sensorValueRowY);
    //ThingSpeak.setField(3,sensorValueRowZ);
	
	//	THINGSPEAK SECTION
	// Write to all fields at once.
	// ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
	// Write to ThingSpeak, field 1, immediately
	//ThingSpeak.writeField(myChannelNumber, 1, sensorValueRowX, myWriteAPIKey);
	

    // Additional info useful while debugging
    //printDebugInfo();
    }
    // If sensor.read() didn't return true you can try again later
    // This next block helps debug what's wrong.
    // It's not needed for the sensor to work properly
      else {
        // Once all sensors have been read you'll get searchDone() == true
        // Next time read() is called the first sensor is read again
        if (sensor.searchDone()) {
            Serial.println("No more addresses.");
            // Avoid excessive printing when no sensors are connected
            delay(250);

        // Something went wrong
        } else {
        // printDebugInfo();
        }
    }
  Serial.println();
  
}
