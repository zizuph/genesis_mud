inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   int i;
   set_short("la cross de\n");
   set_long("The passageway tees here at this small, circular " +
      "chamber constructed of large, stone blocks and submersed " +
      "in nearly two feet of water.  Slimy creatures brush by your " +
      "ankles startling you occasionally and the stench of decay " +
      "and rot has grown to a nearly unbearable level.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item("stone", "The stone here is of a dark, dark almost " +
      "black color that is very dull in luster and reflects " +
      "little light.\n");
   add_item("water","The water is murky, green, and teeming with " +
      "pieces of filth and rot whose origins seem to elude you. " +
      "thin layer of brackish ooze lays atop the rippled water " +
      "interrrupted only by the grungy rats swimming through it.\n");
   add_item(({"block","blocks"}), "These large, dark blocks of " +
      "stone approximately one by two feet in dimension are covered " +
      "with brackish green and black molds and drip slime from tiny " +
      "cracks throughout the mortar.\n");
   for (i = 0; i < 2; i++)
   clone_object("/d/Rhovanion/common/dungeon1/living/rat.c")
   ->move(TO);
   for (i = 0; i < 2; i++)
   clone_object("/d/Rhovanion/common/dungeon1/living/rat3.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/living/rat2.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/living/bats.c")
   ->move(TO);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun25","north");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun24","west");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/int8","south");
}
