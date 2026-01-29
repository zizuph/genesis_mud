#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/clock/clock.h"

/* Inherit the Krynn room */
inherit OR_FILE

#define CREATE "create_vin_mount_room"
#define RESET  "reset_vin_mount_room"

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
              desc = "The sun is rising above the mountaintops, beginning " +
	             "a new day. " + long;
              break;
	case TOD_DAY:
	      desc = "The sun is standing high above the mountains, giving off " +
		     "a pleasant warmth. " + long;
              break;
	case TOD_TWILIGHT:
              desc = "The sun is sinking behind the mountaintops, casting " +
		     "long shadows across the valleys. " + long;
	      break;
	case TOD_NIGHT:
	      desc = "The pale light from the two moons, " + C(SOLINARI) + 
		     " and " + C(LUNITARI) + ", is casting the mountains and " +
		     "valleys into an eerie light. " +
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
