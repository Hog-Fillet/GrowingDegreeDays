// This #include statement was automatically added by the Particle IDE.
#include <OneWire.h>
//#include <DS18B20.h>
#include <ThingSpeak.h>
#include "DS18.h"

TCPClient client;
DS18 sensor(D13);

// ThingSpeak Channel Number and API Key
// **Should change this to be more secure
unsigned long myChannelNumber = 731708;	// change this to your channel number
const char * myWriteAPIKey = "Q2WWASR90N0ZWSJZ"; // ThingSpeak channel write API key
const char * myReadAPIKey = "YH6WIXPDH088X7GO"; // ThingSpeak channel read API key
const char * Xenon1 = "e00fce68bc89905817e6c21b";
const char * Xenon2 = "e00fce68a9eef5d55b0660da";
const char * Argon = "e00fce68348df9102e2d42b6";

float low_temp = 100.0;
float high_temp = 0.0;
float low_temp_x1 = 100.0;
float high_temp_x1 = 0.0;
float low_temp_x2 = 100.0;
float high_temp_x2 = 0.0;
int day = 0;
float GDD = 0.0;
int hightvar = 0;
int lowtvar = 0;
int dayvar = 0;
int gddvar = 0;
int channel_low = 0;
int channel_high = 0;
int channel_GDD = 0;
double temp_mesh = 0;
double voltage = 0;

void myHandler(const char *event, const char *data){
//Serial.println(“event=%s data=%s”, event, data ? data : “NULL”);
//ex: printed event=temp data=23.2

// Change the data back into a number
    temp_mesh = atof(data);
    
    if(strstr(event, Xenon1) != NULL){
      Particle.publish("Found:X1", Xenon1, PRIVATE);
      Particle.publish("X1 temp", data, PRIVATE);
      if (temp_mesh < low_temp_x1){
        low_temp_x1 = temp_mesh;
        Particle.publish("New low X1", String(temp_mesh), PRIVATE);
        ThingSpeak.writeField(myChannelNumber, 3, low_temp_x1, myWriteAPIKey);
      } 
      if (temp_mesh > high_temp_x1){
        high_temp_x1 = temp_mesh;
        Particle.publish("New high X1", String(temp_mesh), PRIVATE);
        ThingSpeak.writeField(myChannelNumber, 4, high_temp_x1, myWriteAPIKey);
      } else {
        Particle.publish("No change X1");
      }
    
    }
    if(strstr(event, Xenon2) != NULL){
      Particle.publish("Found:X2", Xenon2,  PRIVATE);
      Particle.publish("X2 temp", data, PRIVATE);
       if (temp_mesh < low_temp_x2){
        low_temp_x2 = temp_mesh;
        Particle.publish("New low X2", String(temp_mesh), PRIVATE);
        ThingSpeak.writeField(myChannelNumber, 5, low_temp_x2, myWriteAPIKey);
      }
      if (temp_mesh > high_temp_x2){
        high_temp_x2 = temp_mesh;
        Particle.publish("New high X2", String(temp_mesh), PRIVATE);
        ThingSpeak.writeField(myChannelNumber, 6, high_temp_x2, myWriteAPIKey);
      } else {
        Particle.publish("No change X2");
      }
    }

}

void selectExternalMeshAntenna(){

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

void setup() {
// Section for Dallas-1-Wire for DS18
  Serial.begin(9600);
  
// Choose external Mesh antenna
 selectExternalMeshAntenna(); 

  Mesh.subscribe("Xenon", myHandler);

// Setup Particle Variables
  Particle.variable("high_temp", hightvar);
  Particle.variable("low_temp", lowtvar);
  Particle.variable("AM-0 or PM-1", dayvar);
  Particle.variable("GDD", gddvar);
  Particle.variable("Mesh_Temp", temp_mesh);
  Particle.variable("Voltage", voltage);


//Setup which channel to write to
if (Xenon1 == System.deviceID()){
    channel_low = 3;
    channel_high = 4;
    Particle.publish("XENON ", String(1) , 360, PRIVATE);
}
if (Xenon2 == System.deviceID()){
    channel_low = 5;
    channel_high = 6;
    Particle.publish("XENON ", String(1) , 360, PRIVATE);
}
if (Argon == System.deviceID()){
    channel_low = 1;
    channel_high = 2;
    channel_GDD = 7;
    Particle.publish("ARGON ", String(1) , PRIVATE);
}

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
  Particle.publish("AM-0 or PM-1: ", String(day),  PRIVATE);
  
  
//Section for MATLAB ThingSpeak
  ThingSpeak.begin(client);
  waitFor(Time.isValid, 10000);
  
//Re establish high and low temps & GDDs on a new version of code/update/reboot
//  low_temp = ThingSpeak.readFloatField(myChannelNumber, channel_low, myReadAPIKey);
//  high_temp = ThingSpeak.readFloatField(myChannelNumber, channel_high, myReadAPIKey);
//  GDD = ThingSpeak.readFloatField(myChannelNumber, channel_GDD, myReadAPIKey);
  
  low_temp = ThingSpeak.readFloatField(myChannelNumber, 1, myReadAPIKey);
  high_temp = ThingSpeak.readFloatField(myChannelNumber, 2, myReadAPIKey);
  waitFor(Time.isValid, 5000);
  low_temp_x1 = ThingSpeak.readFloatField(myChannelNumber, 3, myReadAPIKey);
  high_temp_x1 = ThingSpeak.readFloatField(myChannelNumber, 4, myReadAPIKey);
  waitFor(Time.isValid, 5000);
  low_temp_x2 = ThingSpeak.readFloatField(myChannelNumber, 5, myReadAPIKey);
  high_temp_x2 = ThingSpeak.readFloatField(myChannelNumber, 6, myReadAPIKey);
  waitFor(Time.isValid, 5000);
  GDD = ThingSpeak.readFloatField(myChannelNumber, 7, myReadAPIKey);
  
// blank ThingSpeak can send back -1
  if (low_temp <= 0)
    low_temp = 100;
  if (high_temp <= 0)
    high_temp = 0;
  if (low_temp_x1 <= 0)
    low_temp_x1 = 100;
  if (high_temp_x1 <= 0)
    high_temp_x1 = 0;
  if (low_temp_x2 <= 0)
    low_temp_x2 = 100;
  if (high_temp_x2 <= 0)
    high_temp_x2 = 0;
    
// Old valid temps found
  if (low_temp != 100){
    Particle.publish("Argon old low temp", String(low_temp),PRIVATE);
    waitFor(Time.isValid, 5000);
  }
  if (high_temp != 0){
    Particle.publish("Argon old high temp", String(high_temp),PRIVATE);
    waitFor(Time.isValid, 5000);
  }
  if (low_temp_x1 != 100){
    Particle.publish("X1 old low temp", String(low_temp_x1),PRIVATE);
     waitFor(Time.isValid, 5000);
  }
  if (high_temp_x1 != 0){
    Particle.publish("X1 old high temp", String(high_temp_x1),PRIVATE);
     waitFor(Time.isValid, 5000);
  }
  if (low_temp_x2 != 100){
    Particle.publish("X2 old low temp", String(low_temp_x2),PRIVATE);
     waitFor(Time.isValid, 5000);
  }
  if (high_temp_x2 != 0){
    Particle.publish("X2 old high temp", String(high_temp_x2),PRIVATE);
     waitFor(Time.isValid, 5000);
  }
  else
    Particle.publish("No old Temps");

}

void loop() {
// Reset the temps on a new day
// PM -> day = 1
// AM -> day = 0
// time is 1553455218
// time is 3/24/19 at 2:20:18 pm
 if (Time.isAM() && day == 1){
        day = 0;
        dayvar = day;
        GDD += ((low_temp+high_temp)/2 - 50);
        ThingSpeak.writeField(myChannelNumber, 7, GDD, myWriteAPIKey);
        gddvar = GDD;
        low_temp = 100.0;
        high_temp = 0.0;
        low_temp_x1 = 100.0;
        high_temp_x1 = 0.0;
        low_temp_x1 = 100.0;
        high_temp_x1 = 0.0;
        Particle.publish("New Day");
    }
 if (Time.isPM() && day == 0){
        day = 1;
        dayvar = day;
        Particle.publish("Afternoon");
    }

// What is the current voltage of the battery
 voltage = analogRead(BATT) * 0.0011224;

// Read the next available 1-Wire temperature sensor
 if (sensor.read()) {

// Check if temp is how high or new low for GDD calculation
    if (sensor.fahrenheit() < low_temp){
        low_temp = sensor.fahrenheit();
        lowtvar = low_temp;
        Particle.publish("New low Argon", String(sensor.fahrenheit()), PRIVATE);
        ThingSpeak.writeField(myChannelNumber, 1, low_temp, myWriteAPIKey);

    } else if (sensor.fahrenheit() > high_temp){
        high_temp = sensor.fahrenheit();
        hightvar = high_temp;
        Particle.publish("New high Argon", String(sensor.fahrenheit()), PRIVATE);
        ThingSpeak.writeField(myChannelNumber, 2, high_temp, myWriteAPIKey);

    } else {
        Particle.publish("No new Argon");
    }
// ThingSpeak will only accept updates every 15 seconds.
// Delay of 60 seconds
	delay(60000); 
}
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
//            delay(10000);
//        }
// Something went wrong

//        else {
        // printDebugInfo();
//        }
//  Serial.println();
  
//}
}
