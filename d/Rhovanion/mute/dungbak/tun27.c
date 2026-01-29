inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("no briefs?!\n");
   set_long("The stone blocked passageway curves sharply here " +
      "heading off to the southwest and east and, you think, " +
      "is slightly slanted down to the south.  The ceiling hangs " +
      "a bit too low as if it were ready to break loose at any " +
      "second and collapse upon you.  The passage is flooded " +
      "with a couple feet of water and the floor feels slimy " +
      "and disgusting.  This place is in serious disrepair.\n");
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
   add_exit("/d/Rhovanion/mute/dungeon1/tun28","southwest");
   add_exit("/d/Rhovanion/mute/dungeon1/tun26","east");
}
