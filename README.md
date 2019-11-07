Info:
<br><ul>
        <li>Gps project, that uses the arduino uno and a nokia 5110 lcd to see your current gps grid.</li>
        <br>
        <li>arduino 1.8.10</li>
<br></ul>
<br>LCD Nokia 5110 lcd shield
<br><ul>
        1.) Pin lay out:
        <ul>
                <li>* rst - 10K resistor - arduino pin 3</li>
<br>            <li>* ce - 1 k resistor - arduino pin 4</li>
<br>            <li>* dc - 10K resistor - arduino pin 5</li>
<br>            <li>* din - 10K resistor - arduino pin 6</li>
<br>            <li>* clk - 10K resistor - arduino pin 7</li>
<br>            <li>* vcc - pwr 5v</li>
<br>            <li>* BL - 330 ohm resistor - pwr 5 v</li>
<br>            <li>* gnd - gnd</li>
<br>            </ul>
<br>
        2.) Driver:
        <ul>
                <li>Nokia_5110_LCD_library-2.1.0</li>
                </ul>
<br>
        3.) Notes:
        <ul>
                <li>added resistors to prevent lcd burn out.</li>
<br>    </ul>
<br></ul>
<br>Adafruit Gps Ulitmate Breakout:
<br><ul>
        <li>1.) Pin lay out:</li>
                <ul>
<br>                    <li>rx - arduino uno pin 0</li>
<br>                    <li>tx - arduino uno pin 1</li>
<br>                    <li>Gnd - gnd</li>
<br>                    <li>vin - 5v Pwr</li>
        </ul>
<br>    <li>2.) Driver:</li>
                 <ul>
<br>                     <li>Adafruit GPS</p></li>
</ul>
</ul>
<br> Known Issues:
<br><ul>
        <li>Gps will parse correctly in serial but will not display correctly on the lcd</li>
</ul
