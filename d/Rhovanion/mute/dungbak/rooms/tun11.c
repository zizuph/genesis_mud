inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("black hole\n");
   set_long("This turn in the passageway is particularly foul " +
      "and slimey.  It reaks of decay and mold and the smell is " +
      "really getting to you.  There's also about two feet of " +
      "water flooding this dilapidated passage.\n");
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
   add_exit("/d/Rhovanion/mute/dungeon1/int4","west");
   add_exit("/d/Rhovanion/mute/dungeon1/int3","south");
}
