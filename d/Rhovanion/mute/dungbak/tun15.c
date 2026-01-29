inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("room\n");
   set_long("The passage bends here and is otherwise " +
      "featureless apart from the large, stone blocks comprising " +
      "the walls and ceiling.  There is a foot of water standing " +
      "here and the smell is atrocious, reminiscent of rot, decay, " +
      "and mold.\n");
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
   add_item("stone", "The stone here is of a dark, dark almost " +
      "black color that is very dull in luster and reflects " +
      "little light.\n");
   add_exit("/d/Rhovanion/mute/dungeon1/int5","south");
   add_exit("/d/Rhovanion/mute/dungeon1/tun16","northeast");
}
