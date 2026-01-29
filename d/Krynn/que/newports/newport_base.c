
#include "local.h"
#include CLOCKH

/* Inherit the Krynn room */
inherit OR_FILE
inherit CONQUER_BASE

string gExtra_night_long, gSpecial_short;

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
    set_area_name(WAR_AREA_NEWPORT);
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
    call_other(TO, RESET);
    reset_conquer_room();
}


public void
set_night_long(string str)
{
    gExtra_night_long = str;
}

public void
set_special_short(string str)
{
    gSpecial_short = str;
}


public string
long_desc(string long)
{
    string str, desc;

    str = (gSpecial_short ? gSpecial_short : short()) +
      ". It is " + GET_TIME_STRING + ". ";

    switch (GET_TIMEOFDAY)
    {
        case TOD_DAWN:
              desc = "The sun is rising above the bushes, beginning " +
	             "a new day. " + long;
              break;
	case TOD_DAY:
	      desc = "The sun is standing high above the plains, giving off " +
		     "a pleasant warmth. " + long;
              break;
	case TOD_TWILIGHT:
              desc = "The sun is sinking below the horizon, the bushes and " +
		"few trees casting long shadows across the plains. " + long;
	      break;
	case TOD_NIGHT:
	      desc = "The pale light from the two moons, " + C(SOLINARI) +
		     " and " + C(LUNITARI) + ", is shining onto the plains " +
		     "allowing you to see your surroundings. " +
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
    ::init();
    init_conquer();
}
