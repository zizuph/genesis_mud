inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("Another one of Mute's places.\n");
   set_long("This is a long, dark passageway " +
      "running west and east.  It is constructed of large, " +
      "stone blocks, is very warm, and there is a horrendous " +
      "scent of some foul wyrm-like beast in the air.  You " +
      "think you feel a hot breeze.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/guard33","west");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/guard31","east");
}
