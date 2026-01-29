inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("tunnel");
   set_long("You are at a turn in the passageway featureless " +
      "except for the large, stone blocks that comprise the walls " +
      "and ceiling, and the solid stone slab that is the floor. " +
      "Dank, stale air pervades these stern halls.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item("stone", "The stone here is of a dark, dark almost black " +
      "that is very dull in luster and reflects little light.\n");
   add_item(({"block","blocks"}), "These are large, dark blocks of " +
      "stone approximately  one by two feet in dimension.  They all " +
      "appear to be nearly identical so you figure they must have been " +
      "worked on by a master stoneworker.\n");
   add_exit("/d/Rhovanion/mute/dungeon1/int10","north");
   add_exit("/d/Rhovanion/mute/dungeon1/tun14","east");
}
