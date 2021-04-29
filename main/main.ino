#include "thermoStates.h"
#include "EncoderMonitor.h"
#include <LiquidCrystal.h>
#define INTERVAL 100

unsigned long timer;
float tempGoal = 100; 
LiquidCrystal LcdDriver (A5, A4, 5, 6, 7, 8);

void setup() {
  // put your setup code here, to run once:
  LcdDriver.begin(16, 2);
  LcdDriver.setCursor(0, 0);
  timer = millis();      // Timer setup.
  analogReference(INTERNAL);
  EncoderInitialize();
}

void loop() {
  // put your main code here, to run repeatedly:
  float measured;// Check time
  String stateToString;
  if (millis() - timer >= INTERVAL)     // if 500 milliseconds, compute voltage and temperature
  {
    
    measured = 1.1 * analogRead(0) / 10.24;
    updateTemp(tempGoal, measured);
    switch(state)
    {
      case STANDBY:
        stateToString = "STANDBY";
        break;
      case HEATING:
        stateToString = "HEATING";
        break;
      case COOLING:
        stateToString = "COOLING";  
        break;   
    }

    tempGoal = (encoderPosition / 16.0) + 70;
    LcdDriver.clear();
    LcdDriver.print(stateToString);
    
    LcdDriver.setCursor(0, 1);
    LcdDriver.print(measured);
    LcdDriver.print("--->");
    LcdDriver.print(tempGoal);
    LcdDriver.setCursor(0, 0);
    timer += INTERVAL;    
  } // End of Timer
  
}
