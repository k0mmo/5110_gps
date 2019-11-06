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
#include <Nokia_LCD.h>

Nokia_LCD lcd(7 /* CLK */, 6 /* DIN */, 5 /* DC */, 4 /* CE */, 3 /* RST */); // pin layout from lcd to uno

// Connect to the GPS on the hardware I2C port
Adafruit_GPS GPS(&Wire);

// Set to 'true' to debug and listen to the raw GPS sentences
#define GPSECHO false

uint32_t timer = millis();


void setup()
{
  while (!Serial);  // waits until Serial is ready

  // connect at 115200 so we can read the GPS fast enough and echo without dropping chars
  Serial.begin(115200);
  lcd.begin(); // starts lcd when powered on
  lcd.setContrast(50); // recomended value between 40 to 60
  lcd.setCursor(0,0); 
  lcd.print("  Gps starting:");
  lcd.setCursor(0,1);
  lcd.print("________________");
  lcd.setCursor(0,3);
  lcd.print("Waiting for fix:");
  Serial.println("Adafruit Gps to arduino uno r3 with nokia 5110 lcd");

  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(0x10);  // The I2C address to use is 0x10
  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time
  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate

  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_ANTENNA);

  delay(1000);

  // Ask for firmware version
  GPS.println(PMTK_Q_RELEASE);
}

void loop() // run over and over again
{
  // read data from the GPS in the 'main loop'
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
  if (GPSECHO)
    if (c) Serial.print(c);
  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences!
    // so be very wary if using OUTPUT_ALLDATA and trying to print out data
    Serial.println(GPS.lastNMEA()); // this also sets the newNMEAreceived() flag to false
    if (!GPS.parse(GPS.lastNMEA())) // this also sets the newNMEAreceived() flag to false
      return; // we can fail to parse a sentence in which case we should just wait for another
  }
  // resets timer if millis() or timer wraps around
  if (timer > millis()) timer = millis();

  // refehes ever 2 seconds
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
      lcd.print("  Gps found");
      lcd.setCursor(0,1);
      lcd.print("Lat: ");
      lcd.print(GPS.latitude, 4); lcd.print(GPS.lat);
      lcd.setCursor(0,2);
      lcd.print("Lng: ");
      lcd.print(GPS.longitude, 4); lcd.println(GPS.lon);
    }
  }
}
