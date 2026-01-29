/*
 * The room base for the Darkenwood area (outside rooms)
 */
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/clock/clock.h"
#include "../road/local.h";
#include <composite.h>
#include <filter_funs.h>

/* Inherit the Krynn room */
inherit OR_FILE

#define CREATE "create_darkenwd_room"
#define RESET  "reset_darkenwd_room"

int gPlace;
string gShort_desc, gLong_desc;

/* Prototypes */

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
        case SHORE:
            gShort_desc = "on the shore of Crystalmir Lake";
	    break;
        case PATH:
	    gShort_desc = "on a forest path";
	    break;
        case ROAD:
	    gShort_desc = "on the Solace-Haven road";
	    break;
	case FOREST:
	    gShort_desc = "in a forest off the Solace-Haven road";   
	    break;
	case TRAIL:
	    gShort_desc = "on a game trail";
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
           desc += "The sunlight flares in the early morning, colouring " +
	           "the sky with brilliant hues of orange and red. ";
	   break;
        case TOD_DAY:
	   desc += "The sun is shining down on you, occasionally " +
	           "disappearing behind a fluffy cloud. ";
	   break;
        case TOD_TWILIGHT:
	   desc += "The sun's rays are fading from view, as the sun " +
	           "sinks behind the horizon. Splashes of purple cover " +
                   "the twilight sky. ";
	   break;
        case TOD_NIGHT:
	   desc += "Light cast from the moons and stars curtains the " +
	           "ground with an eerie glow. ";
	   break;
    }

    desc += check_call(gLong_desc) + " ";

    switch (GET_SEASON)
    {
        case WINTER:
            desc += "Winter's harsh chill blankets the area. All is cold " +
	           "and frozen.";
            break;
	case SPRING:
            desc += "Spring's warming breath awakens the land from its " +
	           "wintertime slumber.";
	    break;
        case SUMMER:
            desc += "Summer's heat produces a land vibrant with life and " +
	           "colour.";
	    break;
	case AUTUMN:
	    desc += "Autumn's coolness prepares the area for the imminent " +
	           "winter chill.";
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
