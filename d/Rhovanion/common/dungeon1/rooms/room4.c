inherit "/std/room.c";
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("saln\n");
   set_long("You now find yourself in a room approximately " +
      "thirty feet square.  Large, stone blocks make up the walls and " +
      "ceiling, and the floor is solid stone interrupted only by a " +
      "deep shaft extending down for nearly four fathoms you guess. " +
      "It's rather dirty here, a thin layer of grime and dirt seems " +
      "to lie atop everything, and the smell is atrocious like the " +
      "rot of a corpse.  A short flight of steps leads down to the " +
      "north and a dark passageway lies just to the south.\n");
   add_item(({ "block", "blocks" }), "These are large, dark blocks of " +
      "stone approximately one by two feet in dimension.  They all " +
      "appear to be nearly identical so you figure they must have been " +
      "worked on by a master stoneworker.\n");
   add_item("stone","The stone in the blocks is very dark and " +
      "lusterless nearly black in color.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/int6","north");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun18","south");
}
