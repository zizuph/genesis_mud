
#include "../local.h"
#include CLOCKH

/* Inherit the Krynn room */
inherit OR_FILE
inherit CONQUER_BASE

#define CREATE "create_splains_room"
#define RESET  "reset_splains_room"

string gExtra_night_long;

/*
 * IN NORMAL CASES YOU SHOULDN'T NEED TO CHANGE ANYTHING BELOW
 */

/*
 * This function is called from the main Krynn room. It checks
 * wether or not the room should be reseted.
 * The function returns TRUE if there should be a reset.
 */
nomask public int
query_reset()
{
    if (function_exists(RESET, TO))
        return 1;

    /* we need to return true all the time, or the warfare module will fail.
     */
    return 1;
    return 0;
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
create_krynn_room()
{
    set_area_name(AREA_NAME);
    call_other(TO, CREATE);
}

/* We redefine set_auto_reset so that no random tables work in these rooms.
 * as long as the warfare module is in operation which takes care of exactly
 * that.
 */
public varargs void
set_auto_reset(string table, int num=1, int slowly=0)
{
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    reset_conquer_room();
    call_other(TO, RESET);
}

public void
set_night_long(string str)
{
    gExtra_night_long = str;
}

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
		       (gExtra_night_long ? gExtra_night_long : long);
	      break;
    }

    str += desc;

    return str;
}

varargs public mixed
long(string str)
{
    string new_long = ::long(str);

    if (!str)
      new_long = long_desc(new_long);

    return new_long;
}

void
init()
{
    init_conquer();
    ::init();
}
