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

#define CREATE "create_flotsam_room"
#define RESET "reset_flotsam_room"

string
tod_descr1()
{
   string str;
   switch (GET_TIMEOFDAY)
   {
      case TOD_NIGHT:
      str = "It is night on the Blood Sea coastline. ";
      break;
      case TOD_DAWN:
      str = "It is morning on the Blood Sea coastline. ";
      break;
      case TOD_DAY:
      str = "It is day on the Blood Sea coastline. ";
      break;
      case TOD_TWILIGHT:
      str = "It is evening on the Blood Sea coastline. ";
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




