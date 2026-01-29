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

#define CREATE "create_dargaard_room"
#define RESET "reset_dargaard_room"
string
tod_descr()
{
   string str;
   switch (GET_TIME_STRING)
   {
      case MIDNIGHT:
      str = "It is the middle of the night. The stars " + 
        "shine brightly in the sky alongside the two moons, Lunitari " + 
        "and Solinari. ";
      break;
      case NIGHT:
      str = "Night has fallen. The soft light of the " + 
        "two moons, Lunitari and Solinari, casts dark shadows on the " + 
        "ground. ";
      break;
      case EARLY_MORNING:
      str = "Bright colours from the rising sun paint the sky above " + 
        "the land. ";
      case MORNING:
      str = "The bright morning sun shines down upon the land. "; 
      break;
      case EVENING:
      str = "The sun's rays are fading from view as the sun sinks " + 
        "below the horizon. ";
      break;
      case NOON:
      str = "The noon sun shines down on the land. ";
      break;
      case AFTERNOON:
      str = "The afternoon sun shines brightly upon the land. ";
      break;
      
   }
   return str;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
    {
       start_room_tells();
    }
}
 
int
no_go()
{
   write("The dense growth of the trees makes it impossible "+
         "to travel in that direction.\n");
   return 1;
}

string
season_descr()
{
   string str;
   switch (GET_SEASON)
   {
      case SPRING:
      str = "A mild spring breeze blows through the air, removing " +
      "some of the chill of winter. ";
      break;
      case SUMMER:
      str = "A warm breeze blows through the air, giving you no " + 
        "relief from the summer heat. ";
      break;
      case AUTUMN:
      str = "A cool wind blows through the air, reminding you that " +
        "winter is not far away. ";
      break;
      case WINTER:
      str = "A cold breeze blows through the air, chilling your bones. ";  
      break;
   }
   return str;
}
 
/*
* IN NORMAL CASES YOU SHOULDN'T NEED TO CHANGE ANYTHING BELOW
*/

/*
* This function is called from the main Krynn room. It checks
* whether or not the room should be reset.
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
   set_tell_time(450);
   add_tell("A cold wind blows through the area, chilling your bones.\n");
   add_tell("A faint scream echoes through the area.\n");
   add_tell("Dark clouds momentaraly block the sun, covering everything in a "+
            "gloomy light.\n");
   add_tell("You feel as if someone is watching you.\n");
}

/*
* This function is called from the main Krynn room.
*/
nomask public void
reset_krynn_room()
{
   call_other(TO, RESET);
}

