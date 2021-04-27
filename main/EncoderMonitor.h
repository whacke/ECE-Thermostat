#ifndef EncoderMonitor_H
#define EncoderMonitor_H

volatile int encoderPosition; //encoder pos can change at any time

void EncoderMonitorA() //interrupt service routines
{
  if(digitalRead(2) == digitalRead(3)) //if input 2 and 3 are equal
  {
    encoderPosition++; //increment encoder Pos
  }
  else
  {
    encoderPosition--; //else decrement encoder Pos
  }
}

void EncoderMonitorB()
{
  if(digitalRead(2) == digitalRead(3)) //if input 2 and 3 are equal
  {
    encoderPosition--; //decrement encoder Pos
  }
  else
  {
    encoderPosition++; //else increment encoder Pos
  }
}

void EncoderInitialize() //start encoder monitoring
{
  pinMode(2, INPUT); //set pins as INPUT
  pinMode(3, INPUT);
  attachInterrupt( digitalPinToInterrupt(2), EncoderMonitorA, CHANGE ); //attach Interrupts to pins
  attachInterrupt( digitalPinToInterrupt(3), EncoderMonitorB, CHANGE );
}

#endif
