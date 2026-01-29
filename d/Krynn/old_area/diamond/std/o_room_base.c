#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include "/d/Krynn/common/clock/clock.h"

inherit OR_FILE

#define CREATE "create_dim_room"
#define RESET "reset_dim_room"

string
tod()
{
   string str;
   switch (GET_TIMEOFDAY)
   {
      case TOD_NIGHT:
      str = "The peace of night permeates the area. ";
      break;
      case TOD_DAWN:
      str = "It is dawn, and the sun splashes the sky with brilliant hues. ";
      break;
      case TOD_DAY:
      str = "The sun sparkles high in the sky. ";
      break;
      case TOD_TWILIGHT:
      str = "It is evening, and the sun splashes the sky with deep hues. ";
      break;
   }
   return str;
}

string
walls()
{
   return "The unblemished white walls of the Diamond City are bright "+
   "and cheerful. Protecting the treasures of culture within, the walls "+
   "serve to compliment the more mystical surrounding fog of the " +
   "island's defences.\n";
}

string
season()
{
   string str;
   switch (GET_SEASON)
   {
      case SPRING:
      str = "Spring dawns upon the Diamond Isle, and rays of sunlight "+ 
	    "make the droplets of the center fountain twinkle as "+
	    "majestic diamonds. ";
      break;
      case SUMMER:
      str = "Summer brings a comfortable warmth to the Diamond Isle. ";
      break;
      case AUTUMN:
      str = "Soft clouds fill the sky over the Diamond Isle. ";
      break;
      case WINTER:
      str = "Refreshing cold invigorates the Diamond Isle and its residents. ";
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
