inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("shit\n");
   set_long("Here the passageway bends a bit.  The large, stone " +
      "blocks that are the walls and ceiling look a little older " +
      "or perhaps just a little more dilapidated then the rest of " +
      "the blocks further west in the passageway.  It's dirtier here, " +
      "too, and the air is very stale.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_exit("/d/Rhovanion/mute/dungeon1/int13","west");
   add_exit("/d/Rhovanion/mute/dungeon1/tun36","southeast");
}
