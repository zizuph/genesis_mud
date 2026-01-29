inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("Disease.\n");
   set_long("This is a tee in this long, dark passageway. " +
      "It is dark, cold, and silent and the only noticeable " +
      "features are its large, stone blocks.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_exit("/d/Rhovanion/mute/dungeon1/guard9","north");
   add_exit("/d/Rhovanion/mute/dungeon1/guard21","west");
   add_exit("/d/Rhovanion/mute/dungeon1/guard23","south");
}
