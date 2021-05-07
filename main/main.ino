#include "thermoStates.h"
#include "EncoderMonitor.h"
#include <LiquidCrystal.h>
#include "ClockBasics.h"
#include "ButtonDebounce.h"
#include <EEPROM.h>
#define INTERVAL 1000

unsigned long timer;
float tempGoal = 0; //temperature goal
int redLight = 9; //red light pin
int blueLight = 10; //blue light pin
int lastEncoder = 0; //initialize encoder integer
//LiquidCrystal LcdDriver (A5, A4, 5, 6, 7, 8);

void setup() {
  // put your setup code here, to run once:
  ButtonInitialize(); //initialize button
  LcdDriver.begin(16, 2);
  LcdDriver.setCursor(0, 0);
  timer = millis();      // Timer setup.
  analogReference(INTERNAL);
  EncoderInitialize(); //initialize encoder
  pinMode(redLight, OUTPUT); //sets red light pin to output
  pinMode(blueLight, OUTPUT); //sets blue light pin to output
  encoderPosition = EEPROM.read(0); //read initial encoder position from EEPROM
  lastEncoder = encoderPosition; //initialize lastEncoder position
  
}

void loop() {
  // put your main code here, to run repeatedly:
  float measured;// Check time
  String stateToString; //string for state message


  switch(ButtonNextState(digitalRead(4))) //Using button state machine
    {
      case 2:
        IncreaseClock(); //on a short press, incement clock values
        LcdDriver.clear();
        SendClock(); //output clock
        break;
  
      case 3:
        MoveClockState(); //on long press, chang the clock state
        LcdDriver.clear();
        SendClock(); //output clock
        break;
    }
  
  if (millis() - timer >= INTERVAL)     // if 1000 milliseconds, compute voltage and temperature
  {
    if(clockState == CLOCK_RUNNING)
      UpdateClock(); //update clock for screen
    LcdDriver.clear(); //clear screen
    LcdDriver.setCursor(0, 0);
    SendClock(); //print clock values
    
    measured = 1.1 * analogRead(0) / 10.24; //compute temperature
    updateTemp(tempGoal, measured);
    switch(state)
    {
      case STANDBY:
        stateToString = " STANDBY"; //update string state
        digitalWrite(redLight, 0); //red off
        digitalWrite(blueLight, 0); //blue off
        break;
      case HEATING:
        stateToString = " HEATING"; //update string state
        digitalWrite(redLight, 1); //red on
        digitalWrite(blueLight, 0); //blue off
        break;
      case COOLING:
        stateToString = " COOLING"; //update string state
        digitalWrite(redLight, 0); //red off
        digitalWrite(blueLight, 1); //blue on
        break;   
    }


    tempGoal = (encoderPosition / 16.0) + 70; //record desired temperature
    if(encoderPosition != lastEncoder) //only write to EEPROM if encoder has changed
    {
      EEPROM.write(0, encoderPosition);
    }
    
    //LcdDriver.clear();
    //SendClock();
    LcdDriver.setCursor(8, 0); //set cursor to 8 on first line
    LcdDriver.print(stateToString); //pring state string
    
    LcdDriver.setCursor(0, 1); //move cursor down
    LcdDriver.print(measured); //print measured value
    LcdDriver.print("--->"); //print arrow for clean output
    LcdDriver.print(tempGoal); //print desired temperature
    LcdDriver.setCursor(0, 0); //reset cursor
    lastEncoder = encoderPosition; //update last encoder position
    timer += INTERVAL;    //update timer
  } // End of Timer
  
}
