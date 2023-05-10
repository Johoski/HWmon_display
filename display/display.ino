#include <Wire.h>
#include <rgb_lcd.h>

rgb_lcd lcd;

int lastCpuUsage = -1;
int lastRamUsage = -1;
int lastGpuUsage = -1;

void setup() {
  lcd.begin(16, 2); // initialize the LCD
  lcd.setRGB(138, 43, 226); // set backlight to a nice purple
  Serial.begin(9600); // initialize the serial port
}

void loop() {
  if (Serial.available()) {
    String str = Serial.readStringUntil('\n'); // read the string from the serial port
    str.trim(); // remove any leading/trailing whitespaces
    int commaIndex1 = str.indexOf(','); // find the first comma separating CPU and RAM usage
    int commaIndex2 = str.indexOf(',', commaIndex1+1); // find the second comma separating RAM and GPU usage
    if (commaIndex1 != -1 && commaIndex2 != -1) {
      // Extract CPU, RAM, and GPU usage percentages
      int cpuUsage = str.substring(0, commaIndex1).toInt();
      int ramUsage = str.substring(commaIndex1 + 1, commaIndex2).toInt();
      int gpuUsage = str.substring(commaIndex2 + 1).toInt();

      // Check if any percentage has changed since the last update
      if (cpuUsage != lastCpuUsage || ramUsage != lastRamUsage || gpuUsage != lastGpuUsage) {
        // Update the LCD display with the new usage percentages
        lcd.setCursor(0, 0); // move cursor to the beginning of the first line
        lcd.print("CPU: "); // display the "CPU" label on the LCD
        lcd.print(cpuUsage); // display the CPU percentage on the LCD
        lcd.print("%  "); // display the "%" symbol and some padding on the LCD
        lcd.print("RAM: "); // display the "RAM" label on the LCD
        lcd.print(ramUsage); // display the RAM percentage on the LCD
        lcd.print("%  "); // display the "%" symbol and some padding on the LCD
        lcd.setCursor(0, 1); // move cursor to the beginning of the second line
        lcd.print("GPU: "); // display the "GPU" label on the LCD
        lcd.print(gpuUsage); // display the GPU percentage on the LCD
        lcd.print("%  "); // display the "%" symbol and some padding on the LCD
        lastCpuUsage = cpuUsage; // update the last CPU usage value
        lastRamUsage = ramUsage; // update the last RAM usage value
        lastGpuUsage = gpuUsage; // update the last GPU usage value
      }
    }
  }
}
