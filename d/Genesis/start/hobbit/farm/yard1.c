/*
 *  The yard of the farm
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>

create_room()
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("Yard");
   set_long(
      "You are on the eastern side of a gate, in the middle of a yard. "
    + "The soil here has been trampled by hoofs. To the west "
    + "is the main building of this farm. The yard continues both "
    + "north and south. East you can leave the yard by the gate.\n");

   add_item("soil",
      "Many animals must have walked here, since the loose soil "
    + "shows marks of all kinds of hoof and footprints. There is "
    + "no particular way they lead to.\n");

   add_exit(STAND_DIR + "yard2","north");
   add_exit(STAND_DIR + "yard5","south");
   add_exit(STAND_PARENT + "v/h_lane4","east");
   add_exit(STAND_DIR + "farm1","west");

   add_prop(ROOM_I_INSIDE, 0);  /* This is an open air room */
}
