inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("no briefs?!\n");
   set_long("The passageway takes another turn here.  " +
      "The walls here are slimey and in disrepair as is the " +
      "ceiling.  There's about two feet of water flooding this passage " +
      "making for slow travel and the smell is horrendous.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item("stone", "The stone here is of a dark, dark almost " +
      "black color that is very dull in luster and reflects " +
      "little light.\n");
   add_item("water","The water is murky, green, and teeming with " +
      "pieces of filth and rot whose origins seem to elude you. " +
      "A thin layer of brackish ooze lays atop the rippled wate.\n");
   add_item(({"block","blocks"}), "These large, dark blocks of " +
      "stone approximately one by two feet in dimension are covered " +
      "with brackish green and black molds and drip slime from tiny " +
      "cracks throughout the mortar.\n");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun28","southeast");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun16","west");
}
