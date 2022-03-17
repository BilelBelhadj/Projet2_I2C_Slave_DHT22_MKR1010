#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>

#define DHTPIN A1     // Digital pin connected to the DHT sensor 
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment the type of sensor in use:
//#define DHTTYPE    DHT11     // DHT 11
#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);

int hum ;
//float tmp = 0.0 ;
unsigned long millisDelay = 2000 ;
unsigned long lastMillis  = 0 ;
unsigned long presentMillis = 0 ;

void setup() {

  Serial.begin(9600);
  // Initialize device.
  dht.begin();

  // initialize wire lib
  Wire.begin();

  // Print temperature sensor details.
  sensor_t sensor;
  //dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);


}


void loop() 
{

    presentMillis = millis();
    if (presentMillis - lastMillis >= millisDelay)
    {
      lastMillis = presentMillis ;
      
      sensors_event_t event;
      /*dht.temperature().getEvent(&event);
      if (isnan(event.temperature)) {
        Serial.println(F("Error reading temperature!"));
      }
      else {
        Serial.print(F("Temperature: "));
        tmp = event.temperature ;
        Serial.print(tmp);
        Serial.println(F("°C"));
        
      }*/
      // Get humidity event and print its value.
      dht.humidity().getEvent(&event);
      if (isnan(event.relative_humidity)) {
        Serial.println(F("Error reading humidity!"));
      }
      else {
        Serial.print(F("Humidity: "));
        hum = event.relative_humidity ;
        Serial.print(hum);
        Serial.println(F("%"));
        

      }
    }

    Wire.beginTransmission(9);     //commence l'envoi avec l'adresse 9 (au peripherique qui va recevoir avec l'adresse 9)
    Wire.write(hum);          //envoi la valeur de potontiometre
    Wire.endTransmission(); 
}