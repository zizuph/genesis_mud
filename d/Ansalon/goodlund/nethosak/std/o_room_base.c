/* 
 * /d/Ansalon/goodlund/nethosak/std/o_room_base.c
 *
 * glain
 *   
 * This it the outdoor base room for all of nethosak.  I just hacked 
 * it from flotsams o_room_base.c.
 *
 */

#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include DL_CLOCK

inherit AOR_FILE

#define CREATE "create_nethosak_room"
#define RESET  "reset_nethosak_room"

string
tod_descr1()
{
   string str;

   switch (GET_TIMEOFDAY)
   {
      case TOD_NIGHT:
      str = "The sun has left the land of Mithas leaving in it's " +
            "wake a cold and windy night.";
      break;
      case TOD_DAWN:
      str = "The first rays of the morning sun are slowly creeping " +
            "over the land.";
      break;
      case TOD_DAY:
      str = "The sun rides high in the sky attempting to bathe the " +
            "cold land in its warmth through the heavy clouds.";
      break;
      case TOD_TWILIGHT:
      str = "The cold night is beginning to settle in as the sun " +
            "leaves the land.";
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
      str = "The night stars are hidden by the storm clouds " +
            "hanging over the land.";
      break;
      case EARLY_MORNING:
      case MORNING:
      str = "The sun is slowly rising over the eastern peaks of " +
            "Argon's Charm.  The clouds are not as heavy toward " +
            "the eastern end of Mithas and the sun can be seen " +
            "poking through them.";
      break;
      case EVENING:
      str = "Hidden by dark storm clouds, the sun can no longer be " +
            "seen making its way over the Blood Sea. ";
      break;
      case NOON:
      case AFTERNOON:
      str = "Lazily drifting across the sky the sun slowly " +
            "approaches the heavy storm clouds over the Blood Sea. ";
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
      str = "A mild spring breeze blows through the city, removing " +
            "some of the chill of winter. ";
      break;
      case SUMMER:
      str = "A humid breeze blows in from the sea. ";
      break;
      case AUTUMN:
      str = "A cool salty wind blows through the city, dispersing " +
            "any remaining trace of the summer's warmth. ";
      break;
      case WINTER:
      str = "An icy winter wind blows in from the mountains, " +
            "chilling the bones.";
      break;
   }
   return str;
}

nomask public int
query_reset()
{
   if (function_exists(RESET, TO))
      return 1;
   return 0;
}

nomask public void
create_krynn_room()
{
   call_other(TO, CREATE);

   remove_item("moons");
   remove_item("lunitari");
   remove_item("solinari");
   remove_item("sun");
}

nomask public void
reset_krynn_room()
{
   call_other(TO, RESET);
}
