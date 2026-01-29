inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("no briefs?!\n");
   set_long("This is a rounded bend in the passageway.  The " +
      "southward slant of the tunnel is so bad here that the " +
      "tunnel is flooded under nearly three feet of water.  It's " +
      "not easy moving through the passage and you feel mushy " +
      "slime under you feet instead of hard stone.\n" +
      "Did something just brush against your leg?\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item("stone", "The stone here is of a dark, dark almost " +
      "black color that is very dull in luster and reflects " +
      "little light.\n");
   add_item("water","The water is murky, green, and teeming with " +
      "pieces of filth and rot whose origins seem to elude you. " +
      "thin layer of brackish ooze lays atop the rippled water\n");
   add_item(({"block","blocks"}), "These large, dark blocks of " +
      "stone approximately one by two feet in dimension are covered " +
      "with brackish green and black molds and drip slime from tiny " +
      "cracks throughout the mortar.\n");
   clone_object("/d/Rhovanion/mute/dungeon1/constrictor.c")->move(TO);
   add_exit("/d/Rhovanion/mute/dungeon1/tun29","northwest");
   add_exit("/d/Rhovanion/mute/dungeon1/tun27","northeast");
}
