// This #include statement was automatically added by the Particle IDE.
#include <OneWire.h>
#include "DS18.h"

DS18 sensor(D13);

const char * Xenon1 = "XXXX1";
const char * Xenon2 = "XXXX2";
const char * Argon = "AAAA1";
double temp = 0;
bool dayornight = true;
float GDD = 0.0;
int hightvar = 0;
int lowtvar = 0;
bool dayvar = true;
double voltage = 0;

void setup() {

// Choose external Mesh antenna
  selectExternalMeshAntenna();
  waitFor(Time.isValid, 5000);
  Mesh.connect();
  Mesh.subscribe("Argon", myHandler);

// Setup Particle Variables
  Particle.variable("temp", temp);
  Particle.variable("AM/PM F/T", dayornight);
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
  if (Time.isAM())
    dayornight = false;
  else
    dayornight = true;
}

void loop() {

// Keep Voltage up to date
 voltage = analogRead(BATT) * 0.0011224;
// Start Publish of temp data to Mesh network

// Read the next available 1-Wire temperature sensor
 if (sensor.read()) {
    temp = sensor.fahrenheit();
    if (Mesh.ready())
        Mesh.publish("Xenon"+System.deviceID(), String(temp));
 }  
 else
    Particle.publish("Mesh not Ready "+System.deviceID(), String(temp), PRIVATE);

// ThingSpeak will only accept updates every 15 seconds.
// Delay of 60 seconds
	delay(60000); 
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

void myHandler(const char *event, const char *data) {
    temp = atof(data);
}
