inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("Bonzer!\n");
   set_long("This tunnel running north and south is only " +
      "five or so feet in width with an eight foot ceiling " +
      "that is arched above you.  The entirety of the tunnel " +
      "is covered with a layer of dust.  It is cold and shabby " +
      "here.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/cell6","north");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/cellint1","south");
}
