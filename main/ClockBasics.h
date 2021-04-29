#ifndef ClockBasics_H
#define ClockBasics_H

LiquidCrystal LcdDriver(A5, A4, 5, 6, 7, 8 ); // This selects the pins to be used.
// Variable used as clock settings.
int CLK_Hours, CLK_Minutes, CLK_Seconds;

// States for setting clock.
enum ClockStates { CLOCK_RUNNING, CLOCK_SET_HOURS,
                   CLOCK_SET_MINUTES, CLOCK_SET_SECONDS
                 };
ClockStates clockState = CLOCK_RUNNING;

// This function is to be called every second
// to update the clock represented by the
// global variables Hours, Minutes, Seconds
void UpdateClock()
{
  // Check if Seconds not at wrap point.
  if (CLK_Seconds < 59)
  {
    CLK_Seconds++; // Move seconds ahead.
  }
  else
  {
    CLK_Seconds = 0; // Reset Seconds
    // and check Minutes for wrap.
    if (CLK_Minutes < 59)
    {
      CLK_Minutes++; // Move seconds ahead.
    }
    else
    {
      CLK_Minutes = 0; // Reset Minutes
      // check Hours for wrap
      if (CLK_Hours < 23)
      {
        CLK_Hours++;// Move Hours ahead.
      }
      else
      {
        CLK_Hours = 0;// Reset Hours
      }// End of CLK_Hours test.
    } // End of Minutes test
  } // End of Seconds test
} // end of UpdateClock()

// Send Hours, Minutes and Seconds to a display.
void SendClock()
{
  //LcdDriver.print(" ");
  // Check if leading zero needs to be sent
  if (CLK_Hours < 10)
  {
    LcdDriver.print("0");
  }
  LcdDriver.print(CLK_Hours); // Then send hours
  LcdDriver.print(":"); // And separator
  // Check for leading zero on Minutes.
  if (CLK_Minutes < 10)
  {
    LcdDriver.print("0");
  }
  LcdDriver.print(CLK_Minutes); // Then send Minutes
  LcdDriver.print(":"); // And separator
  // Check for leading zero needed for Seconds.
  if (CLK_Seconds < 10)
  {
    LcdDriver.print("0");
  }
  LcdDriver.print(CLK_Seconds); // Then send Seconds
  switch ( clockState )
  {
    case CLOCK_RUNNING:
      break;
    case CLOCK_SET_HOURS: //from hours
      LcdDriver.setCursor(1, 0); //go to hours
      break;
    case CLOCK_SET_MINUTES: //from minutes
      LcdDriver.setCursor(3, 0); //go to minutes
      break;
    case CLOCK_SET_SECONDS: //from seconds
      LcdDriver.setCursor(5, 0); //go to seconds
      break;  
  }
  LcdDriver.cursor();
  LcdDriver.blink();
} // End of SendClock()



// Function that processes incoming characters to set the clock.
void SettingClock(int Button, int UpDown )
{
  // interpret input based on state
  switch (clockState)
  {
    case CLOCK_RUNNING:
      if (Button)
      {
        clockState = CLOCK_SET_HOURS;
        CLK_Hours = 0;   // Reset clock values.
        CLK_Minutes = 0;
        CLK_Seconds = 0;
      }
      break;
    case CLOCK_SET_HOURS: // Setting hours
      if ( Button )  // if button was pressed,
      {
        clockState = CLOCK_SET_MINUTES; // move to minutes.
      }
      else
      {
        CLK_Hours += UpDown;  // Adjust hours, 
        if ( CLK_Hours > 23 )  // Wrap at 23 and 0.
          CLK_Hours = 0;
        if ( CLK_Hours < 0 )
          CLK_Hours = 23;
      }
      break;
    case CLOCK_SET_MINUTES: // Repeat above for minutes. 
      if ( Button )
      {
        clockState = CLOCK_SET_SECONDS;
      }
      else
      {
        CLK_Minutes += UpDown;
        if ( CLK_Minutes > 59 )
          CLK_Minutes = 0;
        if ( CLK_Minutes < 0 )
          CLK_Minutes = 59;
      }
      break;
    case CLOCK_SET_SECONDS: // Repeat for seconds.
      if ( Button )
      {
        clockState = CLOCK_RUNNING;
      }
      else
      {
        CLK_Seconds += UpDown;
        if ( CLK_Seconds > 59 )
          CLK_Seconds = 0;
        if ( CLK_Seconds < 0 )
          CLK_Seconds = 59;
      }
      break;

  }// End of clock mode switch.

} // End of SettingClock

void MoveClockState()
{
  switch(clockState) //state machine
  {
    case CLOCK_RUNNING: //from running
      clockState = CLOCK_SET_HOURS; //go to hours
      break;
    case CLOCK_SET_HOURS: //from hours
      clockState = CLOCK_SET_MINUTES; //go to minutes
      break;
    case CLOCK_SET_MINUTES: //from minutes
      clockState = CLOCK_SET_SECONDS; //go to seconds
      break;
    case CLOCK_SET_SECONDS: //from seconds
      clockState = CLOCK_RUNNING; //go to running
      break;  
  }
} //end MoveClockState

void IncreaseClock()
{
  switch(clockState)
  {
    case CLOCK_RUNNING: //don't change if running
      break;
    case CLOCK_SET_HOURS:
      CLK_Hours++; //increment hours
      if(CLK_Hours > 23) //watch for wrap
        CLK_Hours = 0;
      break;
    case CLOCK_SET_MINUTES:
      CLK_Minutes++; //increment mins
      if ( CLK_Minutes > 59 ) //watch for wrap
          CLK_Minutes = 0;
      break;
    case CLOCK_SET_SECONDS:
      CLK_Seconds++; //increment secs
      if ( CLK_Minutes > 59 ) //watch for wrap
          CLK_Minutes = 0;
      break;
  }
}


#endif
