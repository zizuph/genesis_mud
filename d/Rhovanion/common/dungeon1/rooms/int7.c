inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   int i;
   set_short("rat place\n");
   set_long("This is a small room about fifteen feet east and " +
      "west by about twenty feet north and south constructed of " +
      "large, stone blocks and flooded with around a foot of " +
      "water.  The ceiling arches up a few feet, but you're not sure if " +
      "it was actually meant to or if this place is about to " +
      "fall apart on top of you.  The air here is sickly and " +
      "foul;  very hard to breathe.\n");
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
   for (i = 0; i < 3; i++)
   clone_object("/d/Rhovanion/common/dungeon1/living/rat.c")
   ->move(TO);
   for (i = 0; i < 7; i++)
   clone_object("/d/Rhovanion/common/dungeon1/living/rat3.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/living/bats.c")
   ->move(TO);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/int8","north");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun20","west");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun22","south");
}
