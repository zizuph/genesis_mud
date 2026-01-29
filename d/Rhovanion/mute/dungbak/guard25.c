inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("Mute made this, too.\n");
   set_long("You are in a sharp turn in the passageway. " +
      "The walls, a bit less grimey than the rest you've " +
      "seen in this place are made of large, stone blocks " +
      "as is the ceiling.  It is very quiet here.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_exit("/d/Rhovanion/mute/dungeon1/guard24","southwest");
   add_exit("/d/Rhovanion/mute/dungeon1/guard6","south");
}
