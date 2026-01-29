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

#define CREATE "create_ashlar_room"
#define RESET "reset_ashlar_room"

string
tod_descr1()
{
   string str;
   switch (GET_TIMEOFDAY)
   {
      case TOD_NIGHT:
      str = "It is night on the moor. ";
      break;
      case TOD_DAWN:
      str = "It is morning on the moor. ";
      break;
      case TOD_DAY:
      str = "It is day on the moor. ";
      break;
      case TOD_TWILIGHT:
      str = "It is evening on the moor. ";
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
	  str = "A white mist creeps along the ground, ghostly illuminated by " +
	  "the light of the moons. ";
      break;
      case EARLY_MORNING:
      case MORNING:
	  str = "The mist is slowly evaporating as the warmth of the sun spreads. ";
      break;
      case EVENING:
	  str = "The setting sun tints the world a deep blood red. ";
      break;
      case NOON:
      case AFTERNOON:
	  str = "The sun shines down from an almost cloudless sky. ";
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
	  str = "Patches of snow on the ground reveals that winter is not far away. ";
      break;
      case SUMMER:
	  str = "A warm summer breeze blows slowly from the south. ";
      break;
      case AUTUMN:
	  str = "The air has an autumn chill that promises that winter and snow " +
	  "is close by. ";
      break;
      case WINTER:
	  str = "The ground is covered with a layer of snow, and a cold wind blows " +
	  "from the north. ";
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




