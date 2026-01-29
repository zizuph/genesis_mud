/*
 *  Entrance before the cave of the Hin Warriors
 */

inherit "/std/room";

#include "/sys/stdproperties.h"
#include "defs.h"

create_room() {
   set_short("Entrance");
   set_long(break_string(
      "You are standing before a huge cave in the rocks that rise before " 
    + "you. The cave does not look natural. It looks more like "
    + "a handmade hallway leading to the north. Usually this cave entrance is "
    + "guarded. South a path leads down the mountain.\n",70));

   add_exit(HINROOM_DIR + "hall3","north");
   add_exit(HINROOM_DIR + "path1","south");

   add_prop(ROOM_I_INSIDE, 0);  /* This room is outside */
}
