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

#define CREATE "create_seavillage_room"
#define RESET "reset_seavillage_room"

string
tod_descr1()
{
    string str;
    switch (GET_TIMEOFDAY)
    {
    case TOD_NIGHT:
	str = "It is night time in this sea-side village. ";
	break;
    case TOD_DAWN:
	str = "It is dawn in this small village by the sea. ";
	break;
    case TOD_DAY:
	str = "It is day time in this little village by the sea. ";
	break;
    case TOD_TWILIGHT:
	str = "It is evening in this small village by the sea. ";
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
    case NIGHT:
	str = "The silence of night is broken occasionally by the " +
	"mournful cry of a lone seagull wheeling " +
	"high above you, out of sight. ";
	break;
    case EARLY_MORNING:
    case MORNING:
	str = "The rising sun casts an almost blinding glare off " +
	"the breaking waves out to sea, as another day begins " +
	"in the sea-side village. ";
	break;
    case EVENING:
	str = "The setting sun throws off brilliant colours of orange and " +
	"red, as it sinks below the clouds to the south. ";
	break;
    case NOON:
    case AFTERNOON:
	str = "Overhead, the sun casts light over the village, as clouds " +
	"scud across the deep blue sky. ";
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
	str = "A pleasant spring breeze blows through the village, removing " +
	"some of the chill of winter. ";
	break;
    case SUMMER:
	str = "A humid breeze blows in from the sea. The smell of "+
	"rotting fish drifts on the breeze, wrinkling your nose. ";
	break;
    case AUTUMN:
	str = "A cool salty wind blows off the sea and into the village, reminding " +
	"you that winter will be upon you all too soon. ";
	break;
    case WINTER:
	str = "Roaring in off the almost frozen white tops out to " +
	"sea, the bitterly cold wind of winter chills you to the bone. ";
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

}

/*
* This function is called from the main Krynn room.
*/
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}


