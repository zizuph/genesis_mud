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

#define CREATE "create_shadow_room"
#define RESET "reset_shadow_room"

string
tod_descr1()
{
    string str;
    switch (GET_TIMEOFDAY)
    {
    case TOD_NIGHT:
        str = "The constellations representing Paladine and Takhisis seem "+
          "to be missing from the night sky. ";

	break;
    case TOD_DAWN:
        str = "Birds fill the air with their sweet music. ";
	break;
    case TOD_DAY:
        str = "The sun tracks across the sky along its regular course. ";
	break;
    case TOD_TWILIGHT:
        str = "The sound of crickets and night birds fill the air with "+
          "nature's music. ";
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
        str = "The stars fade as the sun comes to take their place. ";
	break;
    case MORNING:
        str = "The sun ascends high into the sky. ";
	break;
    case EVENING:
        str = "The sun shines down from its highest point. ";
        break;
    case NOON:
        str = "The sun shines brightly from its high point in the sky. ";
        break;
    case AFTERNOON:
        str = "The sun descends west behind the trees. ";
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
        str = "Leaves on the trees begin to sprout, and flowers begin "+
          "to bloom. ";
	break;
    case SUMMER:
        str = "Humid air from the Bay of Balifor makes the summer heat "+
          "more uncomfortable. ";
	break;
    case AUTUMN:
        str = "The trees show a stunning display of colors. ";

	break;
    case WINTER:
        str = "A light blanket of snow covers the ground. ";
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




