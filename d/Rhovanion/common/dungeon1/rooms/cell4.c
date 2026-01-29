inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("Aiyee!\n");
   set_long("A thin layer of dust covers the old, dilapidated " +
      "stone of the walls here and the stale, moldy air is making " +
      "breathing difficult.  There is a door set into the " +
      "east wall.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   clone_object("/d/Rhovanion/common/dungeon1/misc/door13.c")->move(TO);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/cell8","north");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/cell3","south");
}
