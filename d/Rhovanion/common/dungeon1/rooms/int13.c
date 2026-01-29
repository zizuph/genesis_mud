inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("int\n");
   set_long("The passageway tees here " +
      "continuing to the east and west and to the north lies a dark, " +
      "particularly long passageway from which a distinct odour of rot " +
      "is present.  The air here however is less so rotten and more " +
      "dusty, dank, and stale.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun34","west");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/store12","north");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun35","east");
}
