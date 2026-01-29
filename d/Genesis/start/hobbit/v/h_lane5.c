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
   set_short("Hill lane");
   set_long(break_string(
      "This is where the Hill lane comes to an end. Around you are green "
    + "pastures on the sides of a hill. North is the entrance to a house. "
    + "Far south you can make out the centre of Hobbiton, across the river "
    + "Bywater.\n",70));

   add_exit(STAND_DIR + "bagend.c","north");
   add_exit(STAND_DIR + "h_lane4","south");

   add_prop(ROOM_I_INSIDE, 0);  /* This is an open air room */
}