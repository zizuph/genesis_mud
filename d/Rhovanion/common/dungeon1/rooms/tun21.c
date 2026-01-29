inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("room\n");
   set_long("You are standing in about a foot of water in " +
      "an east - west running passage of large, stone blocks. " +
      "Disgusting slime and mold cover the walls and foul " +
      "rodents scurry about here through the muck.\n");
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
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun18","west");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun22","east");
   clone_object("/d/Rhovanion/common/dungeon1/living/rat.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/living/rat2.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/living/rat2.c")
   ->move(TO);
}
