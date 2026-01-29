/*
 * Hill lane
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include "/sys/stdproperties.h"

create_room()
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("Hill lane outside mill");
   set_long(
      "You are now standing a few yards way from the base of The Hill. "
    + "There is a narrow sandy road that leads up to the top of it. "
    + "It looks like there are some hobbits that "
    + "have built their houses in the hill. "
    + "To the east is a small watermill. Through the doorway "
    + "you can see some hobbits working. West is the yard of a farm. "
    + "South from here is a bridge that crosses the river. "
    + "The road also continues north.\n");

   add_exit(STAND_DIR + "h_lane5","north");
   add_exit(STAND_DIR + "bridge","south");
   add_exit(STAND_DIR + "mill","east");
   add_exit(STAND_PARENT + "farm/yard1","west");

   add_prop(ROOM_I_INSIDE, 0);  /* This is an open air room */
}