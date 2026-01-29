/*
 * On the Bridge
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include "/sys/stdproperties.h"

create_room()
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("On the bridge over Bywater");
   set_long(break_string(
      "You are now standing on a narrow bridge over Bywater. "
    + "The bridge is so small so there can only be three hobbits "
    + "beside each other. The water in the river looks quite clear and "
    + "you can even see a few fish swimming around. The river is not "
    + "very deep to the east and you are able to make out the bottom. "
    + "There is also a watermill besides the river to the northeast.\n",70));

   add_item("bottom", "The bottom of the Bywater is sandy and rocky.\n");

   add_item(({"river","water"}), break_string(
      "The river Bywater flows from the west to the east. The water "
    + "in the river is very clear. Through it, you can see the sandy "
    + "and rocky bottom of the river.\n",70));

   add_item(({"fish","fishes"}), break_string(
      "The occasional fish you see is some kind of trout, or salmon. "
    + "They are swimming up and down the river in the crystal clear "
    + "water.\n",70));

   add_exit(STAND_DIR+"h_lane4","north");
   add_exit(STAND_DIR+"h_lane1","south");

   add_prop(ROOM_I_INSIDE, 0);  /* This is an open air room */
}
