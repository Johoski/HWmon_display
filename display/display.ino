#include <Wire.h>
#include <rgb_lcd.h>

rgb_lcd lcd;

int lastCpuUsage = -1;
int lastRamUsage = -1;

void setup() {
  lcd.begin(16, 2); // initialize the LCD
  lcd.setRGB(138, 43, 226); // set backlight to white
  Serial.begin(9600); // initialize the serial port
}

void loop() {
  if (Serial.available()) {
    String str = Serial.readStringUntil('\n'); // read the string from the serial port
    str.trim(); // remove any leading/trailing whitespaces
    int commaIndex = str.indexOf(','); // find the comma separating CPU and RAM usage
    if (commaIndex != -1) {
      // Extract CPU and RAM usage percentages
      int cpuUsage = str.substring(0, commaIndex).toInt();
      int ramUsage = str.substring(commaIndex + 1).toInt();
      
      // Check if either percentage has changed since the last update
      if (cpuUsage != lastCpuUsage || ramUsage != lastRamUsage) {
        // Update the LCD display with the new CPU and RAM usage percentages
        lcd.setCursor(0, 0); // move cursor to the beginning of the first line
        lcd.print("CPU "); // display the "CPU" label on the LCD
        lcd.print(cpuUsage); // display the CPU percentage on the LCD
        lcd.print("%"); // display the "%" symbol on the LCD
        lcd.setCursor(8, 0); // move cursor to the beginning of the second line
        lcd.print("RAM "); // display the "RAM" label on the LCD
        lcd.print(ramUsage); // display the RAM percentage on the LCD
        lcd.print("%"); // display the "%" symbol on the LCD
        lastCpuUsage = cpuUsage; // update the last CPU usage value
        lastRamUsage = ramUsage; // update the last RAM usage value
      }
    }
  }
}
