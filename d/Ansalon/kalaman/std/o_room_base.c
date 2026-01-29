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

#define CREATE "create_kalaman_room"
#define RESET "reset_kalaman_room"

string
tod_descr1()
{
    string str;
    switch (GET_TIMEOFDAY)
    {
    case TOD_NIGHT:
	str = "The silence of night seems only to be broken by the sounds of the " +
	"Vingaard River, quietly lapping against the shore. The twin moons, Solinari " +
	"and Lunitari, illuminate its waters in a silvery-red light. ";
	break;
    case TOD_DAWN:
	str = "To your north the golden rays of the morning sun reflect off the " +
	"Vingaard River, the longest river in Ansalon, that flows from the plains " +
	"of Solamnia into the Turbidus Ocean. ";
	break;
    case TOD_DAY:
	str = "The sun shines down brightly onto the great Vingaard River " +
	"to your north, while fluffy white clouds lazily sail across the eternal blue " +
	"sky above you. ";
	break;
    case TOD_TWILIGHT:
	str = "The light of the setting sun sets afire the clouds on the horizon, the " +
	"heavens alight with a sky ranging from pink to a deep purple. To " +
	"your north, the dark waters of the Vingaard River flow silently past " +
	"the city out towards the Turbidus Ocean. ";
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
	str = "No moons or stars light the sky, as billowing black " +
	"storm clouds blow overhead. ";
	break;
    case EARLY_MORNING:
    case MORNING:
	str = "Heavy, black rain clouds overhead begin to lighten to a " +
	"gloomy grey colour, the only indication that the night " +
	"is over and the sun has risen. ";
	break;
    case EVENING:
	str = "Grey storm clouds overhead begin to darken with the " +
	"setting sun. ";
	break;
    case NOON:
    case AFTERNOON:
	str = "Heavy, grey rain clouds drift overhead, blocking out " +
	"any trace of the sun. ";
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
	str = "A mild spring breeze blows through the town, removing " +
	"some of the chill of winter. ";
	break;
    case SUMMER:
	str = "A humid breeze blows in from the sea. ";
	break;
    case AUTUMN:
	str = "A cool salty wind blows through the town, dispersing " +
	"any remaining trace of the summer's warmth. ";
	break;
    case WINTER:
	str = "An icy winter gale blows in from the sea, chilling " +
	"the bones. In the distance, lightning can be seen over " +
	"the ocean, lighting up what looks like an approaching " +
	"storm. ";
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




