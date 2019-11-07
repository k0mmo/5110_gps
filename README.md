Info:
        Gps project, that uses the arduino uno and a nokia 5110 lcd to see your current gps grid.

        arduino 1.8.10

LCD Nokia 5110 lcd shield
        1.) Pin lay out:
                * rst - 10K resistor - arduino pin 3
                * ce - 1 k resistor - arduino pin 4
                * dc - 10K resistor - arduino pin 5
                * din - 10K resistor - arduino pin 6
                * clk - 10K resistor - arduino pin 7
                * vcc - pwr 5v
                * BL - 330 ohm resistor - pwr 5 v
                * gnd - gnd

        2.) Driver:
                * Nokia_5110_LCD_library-2.1.0

        3.) Notes:
                * added resistors to prevent lcd burn out.


Adafruit Gps Ulitmate Breakout:
        1.) Pin lay out:
                * rx - arduino uno pin 0
                * tx - arduino uno pin 1
                * Gnd - gnd
                * vin - 5v Pwr
        2.) Driver:
                * Adafruit GPS 
