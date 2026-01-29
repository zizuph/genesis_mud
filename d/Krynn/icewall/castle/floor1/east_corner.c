/****************************************/
/* East Corner of Icewall Castle*/
/* Coded by Steve*/
/****************************************/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>

inherit ICEINROOM;

create_icewall_room()
{
   set_short("Corner of East Hallway");
   set_long(BS(
         "\nYou are standing at the corner of the east hallway. To"
         + " your south is a small, rotting door. To your west you"
         + " can make out a hallway. There is a small window here"
         + " that looks out over the ice plains. There are cobwebs"
         + " all around the walls and corners."
         + "",75));
   
   add_item("door",
      "This is a small rotten door which lies open.\n");
   add_item("cobwebs",
      "They are just cobwebs.\n");
   add_item("window",
      "You look out the window over the snow plains. You start to shiver.\n");
   
   
   
   add_exit(ICE_CAST1_R + "east_hall.c", "west");
   add_exit(ICE_CAST1_R + "top_stairs.c", "south", "@@yuk");
}

yuk() {
   write("You shudder in disgust as you push "
      + "the slime-covered door open and pass through.\n");
   return 0;
}
