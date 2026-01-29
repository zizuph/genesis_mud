inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("This be Mute's!   Arrrgh!\n");
   set_long("The passageway runs north and south here and the " +
      "walls are covered with a layer of dust.  There is a door " +
      "set into the east wall and the heavy scent of " +
      "decay hangs in the air.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   clone_object("/d/Rhovanion/common/dungeon1/misc/door12.c")->move(TO);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/cell4","north");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/cell2","south");
}
