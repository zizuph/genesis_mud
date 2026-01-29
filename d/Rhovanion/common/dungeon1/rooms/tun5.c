inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("neon X\n");
   set_long("The large, stone blocks comprising the walls are getting " +
      "pretty monotonous making you almost glad to see the tunnel " +
      "turning ahead.  The dank, stale air here is starting to get " +
      "to you as well.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({ "block", "blocks" }), "These are large, dark blocks of " +
      "stone approximately one by two feet in dimension.  They all " +
      "appear to be nearly identical so you figure they must have been " +
      "worked on by a master stoneworker.\n");
   add_item("stone","The stone in the blocks is very dark and " +
      "lusterless nearly black in color.\n");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun4","east");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/int2","northwest");
}
