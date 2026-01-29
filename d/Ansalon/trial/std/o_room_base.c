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
 
string
random_herb()
{
   string str;
   switch (random(58))
   {
      case 0:
      str = "amanita";
      break;
      case 1:
      str = "angeltear";
      break;
      case 2:
      str = "asparagus";
      break;
      case 3:
      str = "bch_plum";  
      break;
      case 4:
      str = "bch_willow";  
      break;
      case 5:
      str = "blk_currant";  
      break;
      case 6:
      str = "brownslime";  
      break;
      case 7:
      str = "bull_kelp";  
      break;
      case 8:
      str = "bunchberry";  
      break;
      case 9:
      str = "cattail";  
      break;
      case 10:
      str = "chantrelle";  
      break;
      case 11:
      str = "chicory";  
      break;
      case 12:
      str = "chokecherry";  
      break;
      case 13:
      str = "cladina";  
      break;
      case 14:
      str = "coral_alga";  
      break;
      case 15:
      str = "cord_grass";  
      break;
      case 16:
      str = "cranberry";  
      break;
      case 17:
      str = "crocus";  
      break;
      case 18:
      str = "dandelion";  
      break;
      case 19:
      str = "eel_grass";  
      break;
      case 20:
      str = "elidross";  
      break;
      case 21:
      str = "elkhorn_kelp";  
      break;
      case 22:
      str = "fdlhead";  
      break;
      case 23:
      str = "fireweed";  
      break;
      case 24:
      str = "fucus";  
      break;
      case 25:
      str = "greenslime";  
      break;
      case 26:
      str = "grey_willow";  
      break;
      case 27:
      str = "hawthorn";  
      break;
      case 28:
      str = "hazelnut";  
      break;
      case 29:
      str = "hop";  
      break;
      case 30:
      str = "horsetail";  
      break;
      case 31:
      str = "jewelweed";  
      break;
      case 32:
      str = "labr_tea";  
      break;
      case 33:
      str = "lady_slipper";  
      break;
      case 34:
      str = "laminaria";  
      break;
      case 35:
      str = "locoweed";  
      break;
      case 36:
      str = "mandrake";  
      break;
      case 37:
      str = "onoclea";  
      break;
      case 38:
      str = "poison_ivy";  
      break;
      case 39:
      str = "raspberry";  
      break;
      case 40:
      str = "salt_wort";  
      break;
      case 41:
      str = "sargassum";  
      break;
      case 42:
      str = "sarsaparilla";  
      break;
      case 43:
      str = "saskatoon";  
      break;
      case 44:
      str = "sea_bubble";  
      break;
      case 45:
      str = "sea_lettuce";  
      break;
      case 46:
      str = "skullcap";  
      break;
      case 47:
      str = "sm_camas";  
      break;
      case 48:
      str = "sea_lettuce";  
      break;
      case 49:
      str = "soapweed";  
      break;
      case 50:
      str = "tiger_lily";  
      break;
      case 51:
      str = "tangleshoot";  
      break;
      case 52:
      str = "surf_grass";  
      break;
      case 53:
      str = "ss_grass";  
      break;
      case 54:
      str = "sphagnum";  
      break;
      case 55:
      str = "solinaith";  
      break;
      case 56:
      str = "veronica";  
      break;
      case 57:
      str = "wild_cuke";  
      break;
      case 58:
      str = "wild_plum";  
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
   add_tell("A cool breeze blows through the forest.\n");
   add_tell("The trees sway slightly in the wind.\n"); 
   add_tell("A small bird flies past you, and disappears "+
            "in the dense canopy.\n");
   add_tell("A tiny deer spots you and quickly disappears "+
            "in between the trees.\n");
   add_tell("The trees sway slightly in the wind.\n"); 
}

/*
* This function is called from the main Krynn room.
*/
nomask public void
reset_krynn_room()
{
   call_other(TO, RESET);
}

