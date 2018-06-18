# SevenSegClock
<b>Description:</b>
<p>Clock using arduino and seven segment displays only</p>

<b>Features include:</b>
- Time in the format HH:MM:SS using six seven segment displays
- Set and Inc buttons to set time
- Time keeping without an RTC (although using an RTC is suggested as time has to be set every time the arduino is reset)

<b>Languages used:</b>
- Arduino

<b>Tools used:</b>
- <a href="https://www.arduino.cc/en/Main/Software/">Arduino IDE</a>

<b>Instructions:</b>
* You donot need any external libraries for this sketch.
* The circuit consists of pins 2-8 connected to a-g of all seven segment displays. Pin 11 is used for the blinking LEDs between hour,minute and second. digitalWrite may be used instead of analogWrite by adding an appropriate resistor.
* The digit to be written is copied from the byte array and written to pins 2-8 which are available at all the dispalys. The corresponding display is the activated by pulling the anode to HIGH and pulling down all other anodes to LOW.
* The code is designed for common anode displays. For common cathode displays, invert digitArray and the states in dispnum() function.
* Pressing the SET button (pin 9) freezes the time and forces the clock to Time Set mode. Pressing once modifies the hour, twice modifies the minute and thrice the seconds. Pressing four times restores normal operation. Press the INCREMENT button (pin 10 ) in  Time Set mode to increment the value of the current variable.
* When using an RTC such as DS1307 or DS3231, replace the loop with the corresponding commands to get time.
