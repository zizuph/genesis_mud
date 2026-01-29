/*
 *  The yard of the farm
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include "/sys/stdproperties.h"

create_room()
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("Yard");
   set_long(
      "You are standing between the farmhouse to the north and the barn "
    + "to the south. South is the entrance of the barn. From within it come "
    + "all kinds of animal sounds. You can go east to the yard or "
    + "south into the barn.\n");

   add_item(({"soil","grass","sandy grass"}),
      "Many animals must have walked here, since the sandy grass "
    + "contains many hoof and footprints. They lead from the barn to "
    + "the east and backwards.\n");

   add_item(({"house","farmhouse"}),
      "The south wall of the farmhouse is made of loose boards. It looks "
    + "like something has been scribbled on one board.\n");

   add_item(({"board","boards"}),
      "On one board is written: Take care! Normal boards are not capable "
    + "of resisting a smash with a hammer. Luckily these are... - Joe.\n");

   add_exit(STAND_DIR + "yard6","east");
   add_exit(STAND_DIR + "barn1","south");

   add_prop(ROOM_I_INSIDE, 0);  /* This is an open air room */
}