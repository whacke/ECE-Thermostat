#ifndef ButtonDebounce_H
#define ButtonDebounce_H

enum states {ButtonIdle, ButtonWait, ButtonHigh, ButtonLow}; // enum of posssible states
states ButtonState = ButtonIdle; //global variable for button state
unsigned long int ButtonTime; //holds time to debounce Switch


int ButtonInitialize()
{
  pinMode(13, OUTPUT); //setup 13 as output
  pinMode(4, INPUT); //setup 4 as input
  digitalWrite(13, LOW); //set 13 to low
}

int ButtonNextState(int button) //function to increase button state
{
  switch(ButtonState) //state machine for button
  {
    case ButtonIdle: //if idle
    if(button == LOW) //if button pressed
    {
      ButtonTime = millis(); //get time
      ButtonState = ButtonWait; //update state
      digitalWrite(13, HIGH); //set 13 to high
    }
    break;

    case ButtonWait: //if waiting
    if(button == HIGH) //released
    { 
      ButtonState = ButtonIdle; //button idle now
      digitalWrite(13, LOW); //set to low
    }
    else 
    {
      if(millis() - ButtonTime >= 5) //pressed
      {
      ButtonState = ButtonLow; //updated to pressed
      digitalWrite(13, LOW); //write low
      return 1; //return state indicator
      }
    }
    break;

    case ButtonLow: //pressed
    if(button == HIGH) //released
    {
      ButtonState = ButtonIdle; //reset state
      if(millis() - ButtonTime > 500) //if the press was long
        return 3; //return long indicator
      return 2; //else return short indicator
    }
    break;
  }
  return 0; //error indicator
}

#endif
