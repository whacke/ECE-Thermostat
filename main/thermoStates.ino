#ifndef thermoStates_H
#define thermoStates_H

enum SMStates { STANDBY, HEATING, COOLING };
SMStates state = STANDBY;

float updateTemp(float tempGoal)
{
  float measuredTemp = default; //could make this part of the method if we only want input in main
  switch(state)
  {
    case STANDBY:
      if(measuredTemp > tempGoal + 5)
      {
        state = COOLING;
      }
      else if(measuredTemp < tempGoal - 5)
      {
        state = HEATING;
      }
      break;

    case HEATING:
      if(measuredTemp >= tempGoal)
      {
        state = STANDBY;
      }
      else
      {
        //do whatever we do when heating
      }
      break;

    case COOLING:
      if(measuredTemp <= tempGoal)
      {
        state = STANDBY;
      }
      else
      {
        //do whatever we do when cooling
      }
      break;
  }
}

#endif
