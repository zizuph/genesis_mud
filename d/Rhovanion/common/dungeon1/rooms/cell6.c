inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("Ya-flu du champe!\n");
   set_long("You are now at a tee in this small, dusty " +
      "tunnel.  To your west a small, dark passageway opens " +
      "up.  At first glance it appears to be similar to the " +
      "one you are in.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/cell7","north");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/store22","west");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/cell5","south");
}
