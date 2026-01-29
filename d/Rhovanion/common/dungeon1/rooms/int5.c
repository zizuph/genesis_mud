inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("none\n");
   set_long("This is a small room about fifteen square in " +
      "size, constructed of large, stone blocks, and flooded " +
      "with a foot of water.  The ceiling is arched very high " +
      "extending deep into the dark depths above you.  It " +
      "smells pretty bad here like a rotted corpse or something.\n");
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
   clone_object("/d/Rhovanion/common/dungeon1/living/bats.c")
   ->move(TO);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun12","west");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun15","north");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/int4","east");
}
