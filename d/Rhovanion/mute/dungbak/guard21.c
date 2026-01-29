inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("I'm back!\n");
   set_long("You stop here at this tee in the long, dark" +
      "passageway that you are in to rest a bit.  From the " +
      "north can be heard loud, raucous noise reminiscent " +
      "of beastial banter, and you can also make out the " +
      "light of torches as well.  The other passageways " +
      "are dark, cold, and silent.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_exit("/d/Rhovanion/mute/dungeon1/guard8","north");
   add_exit("/d/Rhovanion/mute/dungeon1/guard22","east");
   add_exit("/d/Rhovanion/mute/dungeon1/guard20","south");
}
