// This #include statement was automatically added by the Particle IDE.
#include <OneWire.h>
//#include <DS18B20.h>
//#include <ThingSpeak.h>
#include "DS18.h"

//TCPClient client;
DS18 sensor(D13);

// ThingSpeak Channel Number and API Key
// **Should change this to be more secure
const char * Xenon1 = "e00fce68bc89905817e6c21b";
const char * Argon = "e00fce68348df9102e2d42b6";
double temp = 0;
int day = 0;
float GDD = 0.0;
int hightvar = 0;
int lowtvar = 0;
int dayvar = 0;
double voltage = 0;

void setup() {
// Section for Dallas-1-Wire for DS18
  Serial.begin(9600);

// Choose external Mesh antenna
// selectExternalMeshAntenna(); 
  Mesh.connect();
  Mesh.subscribe("Argon", myHandler);

// Setup Particle Variables
  Particle.variable("temp", temp);
  Particle.variable("AM-0 or PM-1", dayvar);
  Particle.variable("Voltage", voltage);
  
// Set up 'power' pins, comment out if not used!
  pinMode(D3, OUTPUT);
  pinMode(D5, OUTPUT);
  digitalWrite(D3, LOW);
  digitalWrite(D5, HIGH);
  
// Wait for time, 60 seconds, to be synchronized with Particle Device Cloud (requires active connection)
  waitFor(Time.isValid, 60000);
  
// Set the time zone for AM/PM check
  Time.zone(-5);
  
// setup for daily wipe of high and low temps
  if (Time.isAM()){
    day = 0;
  } else {
      day = 1;
    }

}

void loop() {

 // Keep Variables up to date
 voltage = analogRead(BATT) * 0.0011224;
// Start Publish of temp data to Mesh network

// Read the next available 1-Wire temperature sensor
 if (sensor.read()) {
     temp = sensor.fahrenheit();
     
    if (Mesh.ready()) {
        Particle.publish("Xenon-"+System.deviceID(), String(temp));
        Mesh.publish("Xenon"+System.deviceID(), String(temp));
//            meshPub = false;
//            meshLost = false;
        }

    } else {
//        Serial.printf("Xenon1 no Temp");
//        Particle.publish("Xenon1 no Temp", String(low_temp+high_temp), PRIVATE);
    }
// ThingSpeak will only accept updates every 15 seconds.
// Delay of 60 seconds
	delay(60000); 

// If sensor.read() didn't return true you can try again later
// This next block helps debug what's wrong.
// It's not needed for the sensor to work properly
//      else {
// Once all sensors have been read you'll get searchDone() == true
// Next time read() is called the first sensor is read again
//        if (sensor.searchDone()) {
//            Serial.println("No more addresses.");
//            Particle.publish("Nothing @", System.deviceID(), PRIVATE);

// Avoid excessive printing when no sensors are connected
//            delay(1000);

// Something went wrong
//        } else {
        // printDebugInfo();
//        }
//    }
//  Serial.println();
}

void selectExternalMeshAntenna() {

#if (PLATFORM_ID == PLATFORM_ARGON)
	digitalWrite(ANTSW1, 1);
	digitalWrite(ANTSW2, 0);
#elif (PLATFORM_ID == PLATFORM_BORON)
	digitalWrite(ANTSW1, 0);
#else
	digitalWrite(ANTSW1, 0);
	digitalWrite(ANTSW2, 1);
#endif
}

void myHandler(const char *event, const char *data)
{
    temp = atof(data);
//Serial.println(“event=%s data=%s”, event, data ? data : “NULL”);
//ex: printed event=temp data=23.2
}
