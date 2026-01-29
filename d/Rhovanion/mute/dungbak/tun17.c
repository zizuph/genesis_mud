inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("Tunnel.\n");
   set_long("This tunnel of large, stone blocks " +
      "is submerged under a foot or so of water.  This section " +
      "of the complex appears to be in a state of dilapidation " +
      "and decay.  It smells rotten here.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item("water","The water is murky, green, and littered with " +
      "pieces of trash you can only guess as to where they came from " +
      "or what they're made of which float on top of the water along " +
      "with a filmy layer of slime.\n");
   add_item(({"block","blocks"}), "These large, dark blocks of " +
      "stone approximately one by two feet in dimension are covered " +
      "with brackish green and black molds and drip slime from tiny " +
      "cracks throughout the mortar.\n");
   add_item("stone","The stone in the blocks is very dark and " +
      "lusterless nearly black in color.\n");
   add_exit("/d/Rhovanion/mute/dungeon1/int3","west");
   add_exit("/d/Rhovanion/mute/dungeon1/int6","east");
}
