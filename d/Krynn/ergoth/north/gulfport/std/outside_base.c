
/*
 * outside_base.c
 * Room base for Gulfport (Northern Ergoth) Outside rooms
 * Copied from the outside_base from Haven
 * Tibbit, 30 April 1998
*/

#include "/d/Krynn/common/clock/clock.h"
#include "../local.h";
#include <composite.h>
#include <filter_funs.h>

/* Inherit the Krynn room */
inherit OR_FILE

#define CREATE "create_gulfport_room"
#define RESET  "reset_gulfport_room"

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
    gShort_desc = "outside in the Ergothian capital "+
        "city of Gulfport";
}

public string
long_desc()
{
    string desc;

    desc = "You are " + gShort_desc + ". It is " + GET_TIME_STRING + ". ";

    switch (GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "Dawn is breaking, the sun rising into the humid, "+
	"foggy early morning sky over Northern Ergoth. ";
	break;
    case TOD_DAY:
	desc += "The sun gazes down upon humid Northern Ergoth from "+
	"its daytime perch. ";
	break;
    case TOD_TWILIGHT:
	desc += "Purples and reds fill the sky as the sun begins " +
	"to set. ";
	break;
    case TOD_NIGHT:
	desc += "Krynn's twin moons color the foggy night sky. ";
	break;
    }

    desc += check_call(gLong_desc) + " ";

    switch (GET_SEASON)
    {
    case WINTER:
	desc += "A thick, fluffy snow is falling upon Northern " +
	"Ergoth, dense but not too cold.";
	break;
    case SPRING:
	desc += "A wet springtime is upon Ergoth, the ocean breezes "+
	"bringing in a moderating coolness to the humid climate.";
	break;
    case SUMMER:
	desc += "A mild Summer heat encompasses Northern Ergoth, " +
	"made moderate by the coolness of arriving ocean breezes.";
	break;
    case AUTUMN:
	desc += "Autumn lies upon Ergoth, humid and beginning to " +
	"cool from the summer's pleasant, temperate climate.";
	break;
    }

    return desc + " ";
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
