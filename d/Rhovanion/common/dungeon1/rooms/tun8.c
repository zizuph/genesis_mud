inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("Tunnel.\n");
   set_long("This is a long, dark tunnel with large, stone " +
      "blocks comprising the walls and ceiling and a flat slab of " +
      "stone for the floor interrupted only by a couple of steps " +
      "leading down to the east.  It's a bit dirty here and the " +
      "air is dank and damp, with an almost sickly cold humidity " +
      "to it.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({ "block", "blocks" }), "These are large, dark blocks of " +
      "stone approximately one by two feet in dimension.  They all " +
      "appear to be nearly identical so you figure they must have been " +
      "worked on by a master stoneworker.\n");
   add_item("stone","The stone in the blocks is very dark and " +
      "lusterless nearly black in color.\n");
   add_item("steps","The steps are carved out of the solid stone block that " +
      "is the floor.  You notice nothing unusual about them.\n");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/int1","southwest");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun9","steps");
}
