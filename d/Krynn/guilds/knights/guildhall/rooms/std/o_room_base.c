#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include "/d/Krynn/common/clock/clock.h"

inherit OR_FILE

#define CREATE "create_vin_room"
#define RESET "reset_vin_room"

string
tod()
{
   string str;
   switch (GET_TIMEOFDAY)
   {
      case TOD_NIGHT:
          str = "Night blankets the area. ";
          break;
      case TOD_DAWN:
          str = "It is dawn, and the sun splashes the sky with brilliant hues. ";
          break;
      case TOD_DAY:
          str = "The sun rests high in the sky. ";
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
   return "The mighty walls of Vingaard surround you. Truly, you "+
   "could not be in a safer place on Krynn, for these walls have "+
   "never been breached. According to legends, Vingaard Keep has "+
   "never fallen to Evil.\n";
}

string
season()
{
   string str;
   switch (GET_SEASON)
   {
      case SPRING:
          str = "Spring dawns in Solamnia, and a cool wind sweeps over "+
          "the land. ";
          break;
      case SUMMER:
          str = "Summer fills the land of Solamnia with warmth. ";
          break;
      case AUTUMN:
          str = "Filled with clouds, the sky is cool and grim in Solamnia. ";
          break;
      case WINTER:
          str = "A chilling wind rolls over the snow covered land of Solamnia. ";
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
   {
      return 1;
   }
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
