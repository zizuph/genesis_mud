/*
 * o_room_base.c
 *
 * This is a standard local room base file for out-door rooms.
 * You should change all those XXX to something more appropiate.
 * If you are doing an area like Pax Tharkas then a proper 
 * replacement for XXX would be 'pax'.
 */

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/clock/clock.h"

/* Inherit the Krynn room */
inherit OR_FILE

/*
 * Change these two XXX to the proper name
 */
#define CREATE "create_tarsis_room"
#define RESET  "reset_tarsis_room"

string gNight_long;
int gPlace;

/* Here all the fun begins */

public string
long_desc(string long)
{
  string str, desc;

  str = short() + ". It is " + GET_TIME_STRING + ". ";

  switch (GET_TIMEOFDAY)
    {
    case TOD_DAWN:
      desc = "The sun is rising above the horizon, beginning " +
	"to beat mercilessly on you. " + long;
      break;
    case TOD_DAY:
      desc = "The sun is beating down on you, making you " +
	"feel hot. " + long;
      break;
    case TOD_TWILIGHT:
      desc = "The sun is sinking behind the horizon, slowly the " +
	"heat turns into a more pleasant temperature. " + long;
      break;
    case TOD_NIGHT:
      desc = "The pale light from the two moons, " + C(SOLINARI) + 
	" and " + C(LUNITARI) + ", is casting the landscape " +
	  "into an eerie light. " +
	    (gNight_long ? gNight_long : long);
      break;
    }

  str += desc;

  return str;
}

/*
 * IN NORMAL CASES YOU SHOULDN'T NEED TO CHANGE ANYTHING BELOW
 */

/*
 * This function is called from the main Krynn room. It checks
 * weather or not the room should be reseted.
 * The function returns TRUE if there should be a reset.
 */
nomask public int
query_reset()
{
    if (function_exists(RESET, TO))
        return 1;
    return 0;
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
create_krynn_room()
{
    call_other(TO, CREATE);
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}

varargs public mixed
long(string str)
{
  string new_long = ::long(str);

  if (!str)
    new_long = long_desc(new_long);

  return new_long;
}

public void
set_night_long(string str)
{
  gNight_long = str;
}

public void
set_place(int i)
{
  gPlace = i;
}
