/****************************************/
/* West Corner of Icewall Castle*/
/* Coded by Stevenson                 */
/****************************************/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>

inherit ICEINROOM;

create_icewall_room()
{
   set_short("Corner of West Hallway");
   set_long(BS(
         "\nYou are standing at the corner of the west hallway which"
         + " leads down to the sleeping quarters of the castle staff."
         + " To your south you can see a large door"
         + "@@snore@@. Above the door"
         + " there is a small sign with the word 'STAFF' written on it."
         + " There is also a small room to your north."
         + "",60));
   
   
   add_item("sign",
      "On the sign there is the word 'STAFF' in big black letters.\n");
   add_item("door",
      "You see a slightly open door@@snore@@.\n");
   
   
   add_exit(ICE_CAST1_R + "staff_sleep.c", "south");
   add_exit(ICE_CAST1_R + "west_hall.c", "east");
   add_exit(ICE_CAST1_R + "staff_bath.c", "north");
}

string snore()
{
   if (("/d/Krynn/icewall/castle/floor1/staff_sleep")->
         check_wiz() != "")
   return ", from behind which\nyou can hear loud snoring";
   return "";
}
