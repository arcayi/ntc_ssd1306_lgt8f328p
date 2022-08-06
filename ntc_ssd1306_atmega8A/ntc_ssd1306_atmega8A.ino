/*
  Smooth NTC Thermistor

  Reads a temperature from the NTC 3950 thermistor,
  smooth and displays it in the default Serial.

  https://github.com/YuriiSalimov/NTC_Thermistor

  Created by Yurii Salimov, May, 2019.
  Released into the public domain.
*/
// #include <Thermistor.h>
#include <NTC_Thermistor.h>
#include <SmoothThermistor.h>

// #define SENSOR_PIN_1             A0
// #define SENSOR_PIN_2             A1
#define REFERENCE_RESISTANCE   10000
#define NOMINAL_RESISTANCE     10000
#define NOMINAL_TEMPERATURE    25
#define B_VALUE                3950
#define ADCRESOLUTION          4095

/**
  Smoothing factor of a temperature value.
*/
#define SMOOTHING_FACTOR 5


#include <Arduino.h>
// #include <U8x8lib.h>
// #include <U8g2lib.h>

// #ifdef U8X8_HAVE_HW_I2C
// #include <Wire.h>
// #endif

// U8X8_SSD1306_128X32_UNIVISION_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);   // Adafruit ESP8266/32u4/ARM Boards + FeatherWing OLED
// U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);  // Adafruit ESP8266/32u4/ARM Boards + FeatherWing OLED

#define N_THERM 2
const static int sensor_pins[2]={A0,A1};

Thermistor* thermistor[N_THERM];

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);

  // Thermistor* originThermistor = new NTC_Thermistor(
  //   SENSOR_PIN,
  //   REFERENCE_RESISTANCE,
  //   NOMINAL_RESISTANCE,
  //   NOMINAL_TEMPERATURE,
  //   B_VALUE,
  //   ADCRESOLUTION
  // );
  for(int i=0; i<N_THERM; i++) {
    thermistor[i] = new SmoothThermistor(
      new NTC_Thermistor(
        sensor_pins[i],
        REFERENCE_RESISTANCE,
        NOMINAL_RESISTANCE,
        NOMINAL_TEMPERATURE,
        B_VALUE,
        ADCRESOLUTION
      ),
      SMOOTHING_FACTOR
    );
  }

  // u8x8.begin();
  // u8x8.setPowerSave(0);
  // u8g2.begin();
  
}

// the loop function runs over and over again forever
void loop() {
  // Reads temperature
  // const double celsius[2];
  char buf1[16];

  // u8g2.clearBuffer();					// clear the internal memory
  // u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  // u8g2.drawStr(0,9,"Temperature(C)");	// write something to the internal memory

  for(int i=0; i<N_THERM; i++) {
    const double celsius = thermistor[i]->readCelsius();
    // Output of information
    // Serial.print("Temperature");
    // Serial.print(i);
    // Serial.print(": ");
    // Serial.print(celsius);
    // Serial.print(" C, \t");

    sprintf(buf1, "%3d.%01d", int(celsius), int(celsius * 10) %10);
    Serial.println(buf1);

    // u8g2.setFont(u8g2_font_10x20_tn );	// choose a suitable font
    // u8g2.drawStr(i*128/N_THERM,31, buf1);	// write something to the internal memory
  }
  Serial.println("");
  // u8g2.sendBuffer();					// transfer internal memory to the display
 
  delay(500); // optionally, only to delay the output of information in the example.
}
