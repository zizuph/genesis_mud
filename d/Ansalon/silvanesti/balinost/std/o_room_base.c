/*
* o_room_base.c
*
* This is a standard local room base file for out-door rooms.
* You should change all those XXX to something more appropiate.
* If you are doing an area like Pax Tharkas then a proper 
* replacement for XXX would be 'pax'.
*/

#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include DL_CLOCK

/* Inherit the Ansalon room */
inherit AOR_FILE

#define CREATE "create_balinost_room"
#define RESET "reset_balinost_room"

string
tod_descr1()
{
    string str;
    switch (GET_TIMEOFDAY)
    {
    case TOD_NIGHT:
	str = "The nighttime stars shine faintly in the sky. ";

	break;
    case TOD_DAWN:
	str = "The sun is rising, bringing light and hope to the city. ";
	break;
    case TOD_DAY:
	str = "The sun today shines a little less brightly than "+
	"the day before. ";
	break;
    case TOD_TWILIGHT:
	str = "The setting sun gives way to a long night. ";
	break;
    }
    return str;
}

string
tod_descr2()
{
    string str;
    switch (GET_TIME_STRING)
    {
    case MIDNIGHT:
	str = "Lunitari rises bringing a red hue to the city. ";
	break;
    case NIGHT:
	str = "Lunitari's pale glow washes the city in a dull red light. ";
	break;
    case EARLY_MORNING:
	str = "Light returns to the city, banishing the darkness for "+
	"a while. ";
	break;
    case MORNING:
	str = "People shuffle about attending to their business. ";
	break;
    case EVENING:
	str = "People return to their houses seeking shelter from the "+
	"darkness of night. ";
	break;
    case NOON:
	str = "The sun reaches its zenith and prepares its descent. ";
        break;
    case AFTERNOON:
	str = "Carrion birds fly through they sky.  They seem to be "+
	"waiting for the city to die. ";
	break;

    }
    return str;
}


string
season_descr()
{
    string str;
    switch (GET_SEASON)
    {
    case SPRING:
	str = "The failure of the trees to regain their leaves is a "+
	"reminder of the desolation that envelops the city. ";
	break;
    case SUMMER:
	str = "The heat of summer only amplifies the stench of decay "+
	"coming from the north. ";
	break;
    case AUTUMN:
	str = "The autumn lacks its usual display of colorful foliage. ";

	break;
    case WINTER:
	str = "A light blanket of snow covers the city, and the bitter "+
	"cold goes right to the bones. ";
	break;
    }
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

    remove_item("moons");
    remove_item("lunitari");
    remove_item("solinari");
    remove_item("sun");
}

/*
* This function is called from the main Krynn room.
*/
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}




