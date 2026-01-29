inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("there's a hidden chest here\n");
   set_long("This is yet another passageway of large, stone blocks. " +
      "It appears similar to all the rest you've been in, and you're " +
      "just beginning to appreciate all the work that's been put into " +
      "its construction.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({ "block", "blocks" }), "These are large, dark blocks of " +
      "stone approximately one by two feet in dimension.  They all " +
      "appear to be nearly identical so you figure they must have been " +
      "worked on by a master stoneworker.\n");
   add_item("stone","The stone in the blocks is very dark and " +
      "lusterless nearly black in color.\n");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/int2","south");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/room2","north");
}
