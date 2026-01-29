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
      "You are south of the entrance to the yard. "
    + "The soil here has been trampled by hoofs and most of the grass "
    + "has been eaten by cattle. Northwest is the main building "
    + "of the farm and southwest is a big barn. South is a pasture where "
    + "the cattle are when it is not in the barn.\n");

   add_item("soil",
      "Many animals must have walked here, since the loose soil "
    + "shows marks of all kinds of hoof and footprints. They seem "
    + "to lead from south to west.\n");

   add_exit(STAND_DIR + "yard1","north");
   add_exit(STAND_DIR + "yard8","south");
   add_exit(STAND_DIR + "yard6","west");

   add_prop(ROOM_I_INSIDE, 0);  /* This is an open air room */
}
