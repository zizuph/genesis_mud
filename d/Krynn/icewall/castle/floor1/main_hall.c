/****************************************/
/* Main Entrance Hall of Icewall Castle */
/* Coded by Steve*/
/****************************************/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>

inherit ICEINROOM;

object husky, door;

reset_icewall_room()
{
   if (!husky) {
      husky=clone_object(ICE_CAST_M+"husky");
      husky->move(TO);
   }
   
   if (!door) {
      door = clone_object(ICE_CAST_O+"housedoor1");
      door->move(TO);
   }
}

void create_icewall_room()
{
   set_short("Main Hall");
   set_long(BS(
         "\nYou are standing in a great hallway that seems to be the "
         + "main entrance to the castle. On the oak panelled walls "
         + "hang the stuffed heads of various wild animals. You can "
         + "smell the warm scent of burning wood coming from the area "
         + "to the north and the sweet smell of cooking comes from your "
         + "east. A large set of stairs lead up onto the next floor "
         + "of the castle. "
         + "",75));
   
   
   add_item("stairs",
      "A red, velvet carpet lines the stairs in front of you\n"
      + "which lead upstairs to the second floor.\n");
   add_item(({"walls","wall"}),
      "The oak panelled walls reflect the warm light around\n"
      + "the room.\n");
   add_item(({"heads","head","stuffed","animals"}),
      "There are various stuffed heads of wild animals adorning\n"
      + "the four walls of the room.\n");
   add_item("door","The door is very solid and adorned with "
      + "thick, iron studs.\n");
   
   add_exit(ICE_CAST1_R + "kitchen.c", "east");
   add_exit(ICE_CAST1_R + "study.c", "west");
   add_exit(ICE_CAST1_R + "north_hall.c", "north");
   add_exit(ICE_CAST2_R + "main_hall.c", "up");
   add_exit(ICE_OUT+"up_stairs3","south","@@door");
   
   reset_icewall_room();
}

door() {
   write("\nYou open the door and let yourself out, closing it behind you.\n");
   return 0;
}
