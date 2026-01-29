/*
 * The room base for the forest north of Solace (outside rooms)
 */
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/clock/clock.h"
#include "/d/Krynn/solace/forest/local.h";
#include <composite.h>
#include <filter_funs.h>

/* Inherit the Krynn room */
inherit OR_FILE

#define CREATE "create_solace_room"
#define RESET  "reset_solace_room"

int gPlace;
string gShort_desc, gLong_desc;

public void
set_place(int i)
{
    gPlace = i;
}

public void
set_short_desc(string str)
{
    gShort_desc = str;
}

public void
set_long_desc(string str)
{
    gLong_desc = str;
}

public void
short_desc()
{
    string str;

    switch (gPlace)
    {
        case FOREST:
            gShort_desc = "in a mixed-woods forest";
	    break;
        case HILL:
	    gShort_desc = "in a hilly terrain";
	    break;
	default:
	    break;
    }
}

public string
long_desc()
{
    string desc;

    desc = "You are " + gShort_desc + ". It is " + GET_TIME_STRING + ". ";

    switch (GET_TIMEOFDAY)
    {
        case TOD_DAWN:
           desc += "The sun is rising above the horizon, displaying " +
	           "brilliant hues of red and orange. ";
	   break;
        case TOD_DAY:
	   desc += "The sun is shining down on you, proud of its power. ";
	   break;
        case TOD_TWILIGHT:
	   desc += "The sun is sinking behind the horizon, bidding farewell " +
	           "to the environment around you. ";
	   break;
        case TOD_NIGHT:
	   desc += "The pale light from the two moons casts an eerie " +
	           "glow upon the ground. ";
	   break;
    }

    desc += check_call(gLong_desc) + " ";

    switch (GET_SEASON)
    {
        case WINTER:
            desc += "The chill of the winter is in the air, and all is pale " +
	           "and frozen.";
            break;
	case SPRING:
            desc += "Spring is in the air, awakening the land from the " +
	           "long winter sleep.";
	    break;
        case SUMMER:
            desc += "The land is vibrant with life and color in the warm " +
	           "summer.";
	    break;
	case AUTUMN:
	    desc += "The air grows chill, and though summer is not long " +
	           "gone you know winter will be here soon.";
	    break;
    }

    return desc + "\n";
}

public string
get_living(string *rooms)
{
   object *inv, *live, room;
   int i;

   inv = ({});

   i = sizeof(rooms);

   while (i--)
       if ((room = find_object(rooms[i])))
           inv += all_inventory(room);

   if (inv && sizeof(inv))
   {
       live = FILTER_LIVE(inv);
       if (sizeof(live))
           return COMPOSITE_LIVE(live);
   }
   return 0;
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

    short_desc();

    set_short(gShort_desc);
    set_long("@@long_desc@@");
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}

