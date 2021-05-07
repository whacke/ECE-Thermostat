#ifndef thermoStates_H
#define thermoStates_H

enum SMStates { STANDBY, HEATING, COOLING }; //state enumerator
SMStates state = STANDBY;

SMStates updateTemp(float tempGoal, float measuredTemp) //state machine
{
  switch(state)
  {
    case STANDBY: //case standby
      if(measuredTemp > tempGoal + 5) //if measured temp > tempGoal by 5
      {
        state = COOLING; //set state to cooling
      }
      else if(measuredTemp < tempGoal - 5) //if measured temp < tempGoal by 5
      {
        state = HEATING; //set state to heating
      }
      break;

    case HEATING: //case heating
      if(measuredTemp >= tempGoal) //if measured temp > temperature goal
      {
        state = STANDBY; //set to standby
      }
      break;

    case COOLING: ..case heating
      if(measuredTemp <= tempGoal) //if measured temp < temperature goal
      {
        state = STANDBY; //set to standby
      }
      break;
  }
}

#endif
