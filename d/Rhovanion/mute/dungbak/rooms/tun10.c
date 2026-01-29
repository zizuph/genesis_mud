inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("Tunnel.\n");
   set_long("The passageway makes a turn here splitting off " +
      "to the north and west and is filled with a foot or so of " +
      "murky, green water.  It's rather filthy here.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}), "These large, dark blocks of " +
      "stone approximately one by two feet in dimension are covered " +
      "with brackish green and black molds and drip slime from tiny " +
      "cracks throughout the mortar.\n");
   add_item("stone","The stone in the blocks is very dark and " +
      "lusterless nearly black in color.\n");
   add_item("water","The water is murky, green, and littered with " +
      "pieces of trash you can only guess as to where they came from " +
      "or what they're made of which float on top of the water along " +
      "with a filmy layer of slime.\n");
   add_exit("/d/Rhovanion/mute/dungeon1/tun9.c","west");
   add_exit("/d/Rhovanion/mute/dungeon1/int3.c","north");
}
