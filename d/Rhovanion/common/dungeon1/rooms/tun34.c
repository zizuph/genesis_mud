inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("int\n");
   set_long("This is a long, dark passageway constructed of " +
      "large, stone blocks extending far to the east and west. " +
      "It's a bit dusty here and the air is dank and stale.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun33","west");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/int13","east");
}
