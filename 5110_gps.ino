/* adapted from Adafruit software serial GPS example
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
 *  rx - pin 8
 *  tx - pin 9
 *  vin - 5v pwr
 *  gnd - gnd 
 */

#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <Nokia_LCD.h>

// you can change the pin numbers to match your wiring:
SoftwareSerial mySerial(9, 8);
Adafruit_GPS GPS(&mySerial);

Nokia_LCD lcd(7 /* CLK */, 6 /* DIN */, 5 /* DC */, 4 /* CE */, 3 /* RST */); // pin layout from lcd to uno

// Set GPSECHO to 'false' to turn off echoing the GPS data, Set to 'true' for debugging and listen to the raw GPS sentences
#define GPSECHO  true

void setup()
{

  // connect at 115200 for quick updates
  Serial.begin(115200);
  delay(5000);
  Serial.println("Gps serial parsing");
  lcd.begin();
  lcd.setContrast(50); // sets lcd contrast, best between 40 and 60
  lcd.setCursor(0,0);
  lcd.print("  Gps Location ");
  lcd.setCursor(0,1);
  lcd.print("_________________");
  lcd.setCursor(0,3);
  lcd.print(" Looking for fix");
  lcd.setCursor(0,4);
  lcd.print("  Please wait");

  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);

  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  
  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  
  GPS.sendCommand(PGCMD_ANTENNA); // checks for antenna status

  delay(1000);
  // Ask for firmware version
  mySerial.println(PMTK_Q_RELEASE);
}

uint32_t timer = millis();
void loop()                     // run over and over again
{
  char c = GPS.read();
  if ((c) && (GPSECHO))
    Serial.write(c);

  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {

    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return;  // we can fail to parse a sentence in which case we should just wait for another
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
      lcd.clear(false);
      lcd.setCursor(0,0);
      lcd.print("Gps signal found");
      lcd.setCursor(0,1);
      lcd.print("Sat# "); lcd.print((int)GPS.satellites);
      lcd.setCursor(0,3); lcd.print("Location:");
      lcd.setCursor(0,4); lcd.print("Lat: "); lcd.print(GPS.latitude, 4); lcd.print(GPS.lat);
      lcd.setCursor(0,5); lcd.print("Lon: "); lcd.print(GPS.longitude, 4); lcd.println(GPS.lon); 
      
    }
  }
}
