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

#define CREATE "create_steppe_room"
#define RESET "reset_steppe_room"

string
tod_descr1()
{
    string str;
    switch (GET_TIMEOFDAY)
    {
    case TOD_NIGHT:
	str = "Above, the moons and stars shine coldly down " +
	"through clear skies upon the plains, as insects begin " +
	"their chorus. ";
	break;
    case TOD_DAWN:
	str = "The morning sun drives away the shadows of night " +
	"as it begins its ascent into the heavens. ";
	break;
    case TOD_DAY:
	str = "Above the midday sun shines down through a " +
	"scattered flock of grey clouds. ";
	break;
    case TOD_TWILIGHT:
	str = "The clouds begin to turn a deep pinky colour as " +
	"the sun begins to drop behind the horizon, and the " +
	"shadows of night begin to return to the plains. ";
	break;
    }
    return str;
}

string
tod_descr3()
{
    string str;
    switch (GET_TIMEOFDAY)
    {
    case TOD_NIGHT:
	str = "It is night in the ancient forest. ";
	break;
    case TOD_DAWN:
	str = "It is morning in the ancient forest. ";
	break;
    case TOD_DAY:
	str = "It is day in the ancient forest. ";
	break;
    case TOD_TWILIGHT:
	str = "It is evening in the ancient forest. ";
	break;

    }
    return str;
}


string
season_descr2()
{
    string str;
    switch (GET_SEASON)
    {
    case SPRING:
	str = "spring";
	break;
    case SUMMER:
	str = "early summer";
	break;
    case AUTUMN:
	str = "late autumn";
	break;
    case WINTER:
	str = "winter";
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
	str = " It is night in the forest.";
	break;
    case EARLY_MORNING:
    case MORNING:
	str = " Through the branches above you, the clouds are " +
	"illuminated with a pale silvery light as the morning " +
	"sun spills over the horizon.";
	break;
    case EVENING:
	str = " Through the canopy above you the sky begins to darken, " +
	"the late afternoon sun being completely engulfed in " +
	"storm clouds.";
	break;
    case NOON:
    case AFTERNOON:
	str = " Through the canopy above you, menacing grey clouds " +
	"begin to gather, hinting at a late storm.";
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
	str = " A fresh spring wind";
	break;
    case SUMMER:
	str = " A dry summer breeze";
	break;
    case AUTUMN:
	str = " A chill autumn wind that hints at snow";
	break;
    case WINTER:
	str = " A bitingly cold winter gale";
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




