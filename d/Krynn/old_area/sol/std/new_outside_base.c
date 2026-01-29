#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/clock/clock.h"

/* Inherit the Krynn room */
inherit OR_FILE

#define CREATE "create_solace_room"
#define RESET  "reset_solace_room"

string gExtra_desc, gExtra_night_desc, gShort_desc;

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

    set_long("@@long_desc");
    set_short(C(gShort_desc));    
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
set_short_desc(string str)
{
    gShort_desc = str;
}

public void
set_extra_line(string str)
{
    gExtra_desc = str;
    gExtra_night_desc = str;
}

public void
set_night_extra_line(string str)
{
    gExtra_night_desc = str;
}

public string
long_desc()
{
    string str, desc;

    str = "You are " + gShort_desc + ". It is " + GET_TIME_STRING + ". ";

    switch (GET_TIMEOFDAY)
    {
        case TOD_DAWN:
              desc = "The sun is rising above the horizon, shrinking the " +
	             "shadows cast from the trees. " + gExtra_desc;
              break;
	case TOD_DAY:
          desc = "The sun is shining pleasantly on you, making you " +
		     "feel warm. " + gExtra_desc;
              break;
	case TOD_TWILIGHT:
              desc = "The sun is sinking behind the trees, making the " +
		     "trees cast long dark shadows. " + gExtra_desc;
	      break;
	case TOD_NIGHT:
	      desc = "The pale light from the two moons, " + C(SOLINARI) + 
		     " and " + C(LUNITARI) + ", makes the trees cast " +
		     "long strange shadows. " + gExtra_night_desc;
	      break;
    }

    str += desc + " ";

    switch (GET_SEASON)
    {
        case WINTER:
            str += "The chill of the winter is in the air, and all is pale " +
	           "and frozen.";
            break;
	case SPRING:
            str += "Spring is in the air, awakening the land from the " +
	           "long winter sleep.";
	    break;
        case SUMMER:
            str += "The land is alive with life and colors in the warm " +
	           "summer.";
	    break;
	case AUTUMN:
	    str += "The air grows chill, and though summer is not long " +
	           "gone you know winter will be here, soon.";
	    break;
    }

    return str + "\n";
}


