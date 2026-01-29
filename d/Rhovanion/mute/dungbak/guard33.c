inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("Another one of Mute's places.\n");
   set_long("This is a long, dark passageway " +
      "running west and east.  It is constructed of large, " +
      "stone blocks, is very warm, and the foul reptilian " +
      "scent in the air is growing stronger.  It seems to " +
      "coming from the west from where a hot breeze floats " +
      "past you.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_exit("/d/Rhovanion/mute/dungeon1/guard34","west");
   add_exit("/d/Rhovanion/mute/dungeon1/guard32","east");
}
