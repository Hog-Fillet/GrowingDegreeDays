// This #include statement was automatically added by the Particle IDE.
#include <ThingSpeak.h>

TCPClient client;

// ThingSpeak Channel Number and API Key
// **Should change this to be more secure
unsigned long myChannelNumber = 000000;	// change this to your channel number
const char * myWriteAPIKey = "XXXXXXXX"; // ThingSpeak channel write API key
const char * myReadAPIKey = "XXXXXXXY"; // ThingSpeak channel read API key
const char * Xenon1 = "XXXX1";
const char * Xenon2 = "XXXX2";
const char * Argon = "AAAA1";

float low_temp_x1 = 100.0;
float high_temp_x1 = 0.0;
float low_temp_x2 = 100.0;
float high_temp_x2 = 0.0;
bool day = true;
float GDD_x1 = 0.0;
float GDD_x2 = 0.0;
int hightvar = 0;
int lowtvar = 0;
bool dayvar = true;
int gddvar = 0;
double temp_mesh = 0;
double voltage = 0;

void myHandler(const char *event, const char *data){
// Change the data back into a number
    temp_mesh = atof(data);
    
    if(strstr(event, Xenon1) != NULL){
 //     Particle.publish("Found:X1", Xenon1, PRIVATE);
 //     Particle.publish("X1 temp", data, PRIVATE);
      if (temp_mesh < low_temp_x1){
        low_temp_x1 = temp_mesh;
        Particle.publish("New low X1", String(temp_mesh), PRIVATE);
        ThingSpeak.writeField(myChannelNumber, 3, low_temp_x1, myWriteAPIKey);
// Thingspeak will only accept updates every 15 seconds
        waitFor(Time.isValid, 15000);
      } 
      if (temp_mesh > high_temp_x1){
        high_temp_x1 = temp_mesh;
        Particle.publish("New high X1", String(temp_mesh), PRIVATE);
        ThingSpeak.writeField(myChannelNumber, 4, high_temp_x1, myWriteAPIKey);
        waitFor(Time.isValid, 15000);
      } else {
        Particle.publish("No change X1");
        }
    }
    if(strstr(event, Xenon2) != NULL){
//      Particle.publish("Found:X2", Xenon2,  PRIVATE);
//      Particle.publish("X2 temp", data, PRIVATE);
       if (temp_mesh < low_temp_x2){
        low_temp_x2 = temp_mesh;
        Particle.publish("New low X2", String(temp_mesh), PRIVATE);
        ThingSpeak.writeField(myChannelNumber, 5, low_temp_x2, myWriteAPIKey);
        waitFor(Time.isValid, 15000);
      }
      if (temp_mesh > high_temp_x2){
        high_temp_x2 = temp_mesh;
        Particle.publish("New high X2", String(temp_mesh), PRIVATE);
        ThingSpeak.writeField(myChannelNumber, 6, high_temp_x2, myWriteAPIKey);
        waitFor(Time.isValid, 15000);
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

// Choose external Mesh antenna
  selectExternalMeshAntenna(); 
// Subscribe to Xenon devices
  Mesh.subscribe("Xenon", myHandler);

// Setup Particle Variables
  Particle.variable("high_temp", hightvar);
  Particle.variable("low_temp", lowtvar);
  Particle.variable("AM-0 or PM-1", dayvar);
  Particle.variable("GDD", gddvar);
  Particle.variable("Mesh_Temp", temp_mesh);
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
    day = false;
  } else {
      day = true;
    }
  
//Section for MATLAB ThingSpeak
  ThingSpeak.begin(client);
  waitFor(Time.isValid, 10000);

  low_temp_x1 = ThingSpeak.readFloatField(myChannelNumber, 1, myReadAPIKey);
  high_temp_x1 = ThingSpeak.readFloatField(myChannelNumber, 2, myReadAPIKey);
  low_temp_x2 = ThingSpeak.readFloatField(myChannelNumber, 3, myReadAPIKey);
  high_temp_x2 = ThingSpeak.readFloatField(myChannelNumber, 4, myReadAPIKey);
  GDD_x1 = ThingSpeak.readFloatField(myChannelNumber, 5, myReadAPIKey);
  GDD_x2 = ThingSpeak.readFloatField(myChannelNumber, 6, myReadAPIKey);

  
// blank ThingSpeak can send back -1
  if (low_temp_x1 <= 0)
    low_temp_x1 = 100;
  if (high_temp_x1 <= 0)
    high_temp_x1 = 0;
  if (low_temp_x2 <= 0)
    low_temp_x2 = 100;
  if (high_temp_x2 <= 0)
    high_temp_x2 = 0;
    
// Old valid temps found
  if (low_temp_x1 != 100){
    Particle.publish("X1 old low temp", String(low_temp_x1),PRIVATE);
     waitFor(Time.isValid, 15000);
  }
  if (high_temp_x1 != 0){
    Particle.publish("X1 old high temp", String(high_temp_x1),PRIVATE);
     waitFor(Time.isValid, 15000);
  }
  if (low_temp_x2 != 100){
    Particle.publish("X2 old low temp", String(low_temp_x2),PRIVATE);
     waitFor(Time.isValid, 15000);
  }
  if (high_temp_x2 != 0){
    Particle.publish("X2 old high temp", String(high_temp_x2),PRIVATE);
     waitFor(Time.isValid, 15000);
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
 if (Time.isAM() && day == true){
        day = false;
        dayvar = day;
        GDD_x1 += ((low_temp_x1+high_temp_x2)/2 - 50);
        GDD_x2 += ((low_temp_x2+high_temp_x2)/2 - 50);
        gddvar = GDD_x1;
        if ((GDD_x1 >=0 ) && (GDD_x2 >=0)){
            ThingSpeak.setField(5, GDD_x1);
            ThingSpeak.setField(6, GDD_x2);
            ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
        }
        low_temp_x1 = 100.0;
        high_temp_x1 = 0.0;
        low_temp_x2 = 100.0;
        high_temp_x2 = 0.0;
        Particle.publish("New Day");
    }
 if (Time.isPM() && day == false){
        day = true;
        dayvar = day;
        Particle.publish("Afternoon");
    }

// What is the current voltage of the battery
 voltage = analogRead(BATT) * 0.0011224;
 waitFor(Time.isValid, 120000);

}
