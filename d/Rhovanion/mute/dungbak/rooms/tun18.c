inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("room\n");
   set_long("The passageway turns sharply here.  To the east " +
      "lie a few steps leading down into darkness and by the " +
      "reflectiveness of the floor further east into " +
      "more water as well.\n");
   add_item(({ "block", "blocks" }), "These are large, dark blocks of " +
      "stone approximately one by two feet in dimension.  They all " +
      "appear to be nearly identical so you figure they must have been " +
      "worked on by a master stoneworker.\n");
   add_item("stone","The stone in the blocks is very dark and " +
      "lusterless nearly black in color.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_exit("/d/Rhovanion/mute/dungeon1/trap2.c","north");
   add_exit("/d/Rhovanion/mute/dungeon1/tun21.c","steps");
}
