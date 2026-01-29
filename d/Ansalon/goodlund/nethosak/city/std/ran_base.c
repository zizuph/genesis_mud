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

#define CREATE "create_mithas_room"
#define RESET "reset_mithas_room"
 string
tod_descr()
{
   string str;
   switch (GET_TIME_STRING)
   {
      case MIDNIGHT:
      str = "It's the middle of the night. The stars " + 
        "shine brightly in the sky alongside the two moons, Lunitari " + 
        "and Solinari. ";
      break;
      case NIGHT:
      str = "Night has fallen. The soft light of the " + 
        "two moons, Lunitari and Solinari, draws dark shadows on the " + 
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
      str = "The heat of the afternoon sun shines brightly upon " + 
        "the land. ";
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

string
random_descr()
{
   string str;
   switch (random(2))
   {
      case 0:
      str = "A humid breeze blows in from the sea. ";
      break;
      case 1:
      str = "A tall iron brazier stands off on a sidewalk, relieving "+
            "little of the gloom brought on by the clouds overhead. ";
      break;
      case 2:
      str = "You notice that those who wander the streets are almost "+
            "exclusively part of the occupying dragonarmy. ";
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
   set_tell_time(200);
   add_tell("You hear loud cheers coming from the Arena.\n");
   add_tell("A minotaur patrol passes you, looking suspiciously "+
            "at your weapons.\n");
   add_tell("A bunch of gully dwarves runs away from you.\n");
   add_tell("You hear loud laughter from nearby.\n"); 
   add_tell("A kender approches, he clumsily bumps into "+
            "you but quickly disappears down an alley.\n");
   add_tell("You notice a group of minotaurs pointing at you.\n"); 

   add_item(({"path", "road"}), "The road "+
     "is very orderly, nearly unblemished. The lane is "+
     "covered in stone, so that it almost looks like the "+
     "structures around it is melted into the road.\n");
   add_item(({"building", "buildings", "house", "houses"}), "The "+
     "buildings are very beautiful and they seem very clean and "+
     "new, though many might be centuries old.  Towering above "+
     "all the other buildings is a large house with a wide "+
     "edifice and an arched roof, this must be the palace of "+
     "the emperor.\n");
}

/*
* This function is called from the main Krynn room.
*/
nomask public void
reset_krynn_room()
{
   call_other(TO, RESET);
}

