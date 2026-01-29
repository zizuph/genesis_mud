/*
 * specific routines for captains of newbie ships
 * Tapakah, 05/2009
 */

#include "/d/Genesis/gsl_ships/ships.h"
#include "newbie_ship.h"

inherit STDCAPTAIN;

int
query_ride_for_free (object candidate)
{
	if(interactive(candidate) && candidate->query_average() <= MAX_PASSENGER_AVG/2)
		return 1;
	return 0;
}

int
buy(string str)
{
	if(interactive(TP) && TP->query_average() < MAX_PASSENGER_AVG) {
    return ::buy(str);
  }
  NF0("Only young people can buy tickets for this line, sorry.\n");
  return 0;
}
  
