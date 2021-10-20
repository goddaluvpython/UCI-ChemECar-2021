#include <DFRobot_TCS34725.h>
#include "DFRobot_TCS34725.h"
/*This file utilizes the DFRobot library to 
  interface the TCS34725 library, look at the library headers for
  things to use */

//integration time is 154ms
// 2_4,    24,    50,   101,   154,   700 | possible times (ms)
//1024, 10240, 20480, 43008, 65358, 65358 | max count
//higher integration time is more accurate but refreshes slower
DFRobot_TCS34725 tcs = DFRobot_TCS34725(TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_4X);

void setup() {
  //must set baud to 115200 in the serial monitor!
  Serial.begin(115200);
  Serial.println("Color View Test!");
  //if sensor is on then do things else, halt
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }
}

void loop() {
  //clear is the sum of all 3, RGB are self-explanatory
  //see above for max values depending on integration time
  uint16_t clear, red, green, blue;
  tcs.getRGBC(&red, &green, &blue, &clear);
  tcs.lock();  // turn off LED (doesn't work on the new sensors)
  Serial.print("C:\t"); Serial.print(clear);
  Serial.print("\tR:\t"); Serial.print(red);
  Serial.print("\tG:\t"); Serial.print(green);
  Serial.print("\tB:\t"); Serial.print(blue);
  Serial.println("\t");

  // Figure out some basic hex code for visualization
  uint32_t sum = clear;
  float r, g, b;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256; g *= 256; b *= 256;
  Serial.print("\t");
  Serial.print((int)r, HEX); Serial.print((int)g, HEX); Serial.print((int)b, HEX);
  Serial.println();
}
