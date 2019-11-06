/* adapted from Adafruit I2C GPS example
 *  
 *  Lcd pin lay out:
 *  rst - 10K resistor - arduino pin 3
 *  ce - 1 k resistor - arduino pin 4
 *  dc - 10K resistor - arduino pin 5
 *  din - 10K resistor - arduino pin 6
 *  clk - 10K resistor - arduino pin 7
 *  vcc - pwr 5v
 *  BL - 330 ohm resistor - pwr 5 v
 *  gnd - gnd
 *  
 *  Gps pin layout:
 */
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

// change numbers to match wireing
SoftwareSerial mySerial(0, 1);

Adafruit_GPS GPS(&mySerial);

// Set GPSECHO to 'false' to turn off echoing the GPS data, set to true for debugging and raw sentences
// Set to 'true' if you want to debug and listen to the raw GPS sentences
#define GPSECHO  true

void setup()
{

  // connect at 115200 
  Serial.begin(115200);
  delay(5000);
  Serial.println("Adafruit GPS library basic test!");

  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);

  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  
  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  
  // checks to see if antenna is connected or not
  GPS.sendCommand(PGCMD_ANTENNA);

}

uint32_t timer = millis();

void loop()                     // run over and over again
{
  char c = GPS.read();
  if ((c) && (GPSECHO))
    Serial.write(c);

  
  if (GPS.newNMEAreceived()) {
    
    (GPS.parse(GPS.lastNMEA())); 
  }

  // if millis() or timer wraps around, we'll just reset it
  if (timer > millis())  timer = millis();

  // approximately every 2 seconds or so, print out the current stats
  if (millis() - timer > 2000) {
    timer = millis(); // reset the timer

    Serial.print("\nTime: ");
    if (GPS.hour < 10) { Serial.print('0'); }
    Serial.print(GPS.hour, DEC); Serial.print(':');
    if (GPS.minute < 10) { Serial.print('0'); }
    Serial.print(GPS.minute, DEC); Serial.print(':');
    if (GPS.seconds < 10) { Serial.print('0'); }
    Serial.print(GPS.seconds, DEC); Serial.print('.');
    if (GPS.milliseconds < 10) {
      Serial.print("00");
    } else if (GPS.milliseconds > 9 && GPS.milliseconds < 100) {
      Serial.print("0");
    }
    Serial.println(GPS.milliseconds);
    Serial.print("Date: ");
    Serial.print(GPS.day, DEC); Serial.print('/');
    Serial.print(GPS.month, DEC); Serial.print("/20");
    Serial.println(GPS.year, DEC);
    Serial.print("Fix: "); Serial.print((int)GPS.fix);
    Serial.print(" quality: "); Serial.println((int)GPS.fixquality);
    if (GPS.fix) {
      Serial.print("Location: ");
      Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
      Serial.print(", ");
      Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);

      Serial.print("Speed (knots): "); Serial.println(GPS.speed);
      Serial.print("Angle: "); Serial.println(GPS.angle);
      Serial.print("Altitude: "); Serial.println(GPS.altitude);
      Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
    }
  }
}
