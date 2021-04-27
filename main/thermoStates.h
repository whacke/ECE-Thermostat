#ifndef thermoStates_H
#define thermoStates_H

enum SMStates { STANDBY, HEATING, COOLING };
SMStates state = STANDBY;

SMStates updateTemp(float tempGoal, float measuredTemp)
{
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
