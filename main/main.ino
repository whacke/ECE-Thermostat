#include "thermoStates.h"
#include "EncoderMonitor.h"
#include <LiquidCrystal.h>
#include "ClockBasics.h"
#include "ButtonDebounce.h"
#include <EEPROM.h>
#define INTERVAL 1000

unsigned long timer;
float tempGoal = 0; 
int redLight = 9;
int blueLight = 10;
int lastEncoder = 0;
//LiquidCrystal LcdDriver (A5, A4, 5, 6, 7, 8);

void setup() {
  // put your setup code here, to run once:
  ButtonInitialize(); //initialize button
  LcdDriver.begin(16, 2);
  LcdDriver.setCursor(0, 0);
  timer = millis();      // Timer setup.
  analogReference(INTERNAL);
  EncoderInitialize();
  pinMode(redLight, OUTPUT);
  pinMode(blueLight, OUTPUT);
  encoderPosition = EEPROM.read(0);
  lastEncoder = encoderPosition;
  
}

void loop() {
  // put your main code here, to run repeatedly:
  float measured;// Check time
  String stateToString;


  switch(ButtonNextState(digitalRead(4))) //Using button state machine
    {
      case 2:
        IncreaseClock(); //on a short press, incement clock values
        LcdDriver.clear();
        SendClock();
        break;
  
      case 3:
        MoveClockState(); //on long press, chang the clock state
        LcdDriver.clear();
        SendClock();
        break;
    }
  
  if (millis() - timer >= INTERVAL)     // if 1000 milliseconds, compute voltage and temperature
  {
    if(clockState == CLOCK_RUNNING)
      UpdateClock(); //update clock for screen
    LcdDriver.clear(); //clear screen
    LcdDriver.setCursor(0, 0);
    SendClock(); //print clock values
    
    measured = 1.1 * analogRead(0) / 10.24;
    updateTemp(tempGoal, measured);
    switch(state)
    {
      case STANDBY:
        stateToString = " STANDBY";
        digitalWrite(redLight, 0);
        digitalWrite(blueLight, 0);
        break;
      case HEATING:
        stateToString = " HEATING";
        digitalWrite(redLight, 1);
        digitalWrite(blueLight, 0);
        break;
      case COOLING:
        stateToString = " COOLING";  
        digitalWrite(redLight, 0);
        digitalWrite(blueLight, 1);
        break;   
    }


    tempGoal = (encoderPosition / 16.0) + 70;
    if(encoderPosition != lastEncoder)
    {
      EEPROM.write(0, encoderPosition);
    }
    
    //LcdDriver.clear();
    //SendClock();
    LcdDriver.setCursor(8, 0);
    LcdDriver.print(stateToString);
    
    LcdDriver.setCursor(0, 1);
    LcdDriver.print(measured);
    LcdDriver.print("--->");
    LcdDriver.print(tempGoal);
    LcdDriver.setCursor(0, 0);
    lastEncoder = encoderPosition;
    timer += INTERVAL;    
  } // End of Timer
  
}
