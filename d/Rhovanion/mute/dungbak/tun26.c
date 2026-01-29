inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   int i;
   set_short("Aye, yai, yai!  You're in a pit!\n");
   set_long("This passageway of large, stone blocks flooded " +
      "with about two feet of water reaks of the rotted corpse " +
      "floating on its surface slowly being torn apart by rats. " +
      "The walls are slimy and ooze brackish green gack from the " +
      "cracks between the blocks.  It is truly foul here.\n");
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
   clone_object("d/Rhovanion/mute/dungeon1/corpse.c")->move(TO);
   for (i = 0; i < 5; i++)
   clone_object("d/Rhovanion/mute/dungeon1/rat.c")->move(TO);
   add_exit("/d/Rhovanion/mute/dungeon1/tun27","west");
   add_exit("/d/Rhovanion/mute/dungeon1/tun25","southeast");
}
