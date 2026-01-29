/*
 *    Base file for the out door rooms of the 
 *    example files in Ansalon.
 *
 *    o_room_base.c
 *    -------------
 *
 *    Coded ........: 95/10/03
 *    By ...........: Jeremiah
 *
 *    Latest update : 95/10/03
 *    By ...........: Jeremiah
 */

#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/common/examples/local.h"
#include DL_CLOCK

/* Inherit the Ansalon room */
inherit AOR_FILE

/*
 *    IMPORTANT! .. These two constants must be defined.
 *    ---------- 
 *                  the 'example' from the definitions
 *                  below, has to be replaced with the 
 *                  the general name for the area for 
 *                  which the base file is being coded.
 *
 *                  Ex.: #define CREATE "create_pax_room"
 *                  (Would be appropriate for a base file
 *                  being coded for the Pax Tharkas area.)
 *
 */

#define CREATE "create_example_room"
#define RESET "reset_example_room"


string
tod_descr1()
{
    string str;

    switch (GET_TIMEOFDAY)
    {
      case TOD_NIGHT:
           str = "It is night in the realms of Estwilde. ";
	   break;

	   case TOD_DAWN:
           str = "It is morning in the realms of Estwilde. ";
	   break;

	   case TOD_DAY:
           str = "It is day in the realms of Estwilde. ";
	   break;

	   case TOD_TWILIGHT:
           str = "It is evening in the realms of Estwilde. ";
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
            str = "The stars are shining brightly from the " +
                "sky above you, bathing the area in a " +
                "wonderous pale light. ";
       break;
       case EARLY_MORNING:
            str = "The morning sun is slowly rising from " +
                "below the horizon, chasing away the " +
                "darkness. ";
       break;
       case MORNING:
       case NOON:
       case AFTERNOON:
            str = "The sun is shining from a clear blue " +
                "sky. ";
       break;
        case EVENING:
             str = "The setting suns throws its last light " +
                 "across the land, creating long and strange " +
                 "shadows. ";
        break;
   }
    return str;
}


string
season_descr()
{
    string str;

    switch(GET_SEASON)
    {
        case SPRING:
             str = "The mild spring air lets you know " +
                 "that summer is close. ";
        break;
        case SUMMER:
             str = "A gentle summer breeze is blowing across " +
                 "the area. ";
        break;
        case AUTUMN:
             str = "There is a chill in the autumn air, " +
                 "a reminder about the approaching winter. ";
        break;
        case WINTER:
             str = "A cold winter wind is sweeping across " +
                 "the area. ";
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

