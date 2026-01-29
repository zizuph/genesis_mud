
/***************************************************/
/* Top of Stairs of in Basment of Icewall Castle   */
/*              Coded by Steve             */
/***************************************************/



#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>

inherit ICEINROOM;

create_icewall_room()
{
   set_short("Top of Stairs in Basement");
   set_long(BS(
         "\nYou are standing at the top of the stairs in the basement."
         + " There is a flight of rickety old stairs leading down into the"
         + " the basement which look rotten. This place smells very damp"
         + " and old and the amount of dust suggests that not many"
         + " people have been down here recently. In the distance you"
         + " can hear the sound of a dripping tap."
         + "",75));
   
   add_item(({"stair","stairs"}),
      "The flight of stairs lead down into the basement.\n"
      + "You should be able to make it down them if you are careful.\n");
   
   
   add_exit(ICE_CAST1_R + "east_corner.c", "north");
   add_exit(BASE+"basement","down");
}
