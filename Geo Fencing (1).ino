#include <Arduino.h>
#include "NMEAGPS.h"

NMEAGPS gps;
gps_fix fix; // the current GPS fix
HardwareSerial & gps_port = Serial2; // an alias

NeoGPS::Location_t home( 254139360L, 682662360L ); // degrees * 10,000,000
const float thresholdDistance = 1.00;       //km
// 
uint8_t gpsSeconds; // for counting elapsed time instead of using delay

void setup()
{
  Serial.begin(9600);
  Serial.println("Started...");

  gps_port.begin(9600);

} // setup

void loop()
{
  while (gps.available( gps_port )) 
  {
    fix = gps.read(); // save the current

    // Instead of delay, count the number of GPS fixes
    gpsSeconds++;
    if (gpsSeconds >= 3) 
    {
      gpsSeconds = 0;

      display_info();
      check_dist();
    }
  }
} // loop

void display_info()
{
  Serial.print("Position: ");

  if (fix.valid.location) {
    Serial.print("lat: "); Serial.print(fix.latitude(), 6); Serial.print(" ");// print latitude
    Serial.print("lon: "); Serial.println(fix.longitude(), 6); // print longitude
  } 
  else
    Serial.println( '?' );

} //end displayInfo()

void check_dist()
{
  if (fix.valid.location) {
    float dist = fix.location.DistanceKm( home );

    if (dist >= thresholdDistance )
    {
      Serial.print("Subject is ");
      Serial.print(dist - thresholdDistance, 6); // Threshold - fixed gpsssss
      Serial.println("KM beyond threshold");
    }
    else
    {
      Serial.println("Subject within threshold, no worries!");
    }
  }
}