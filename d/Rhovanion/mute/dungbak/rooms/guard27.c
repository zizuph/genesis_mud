inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("If you haven't noticed by now " +
      "I don't code shorts.  Please switch to unbrief.\n");
   set_long("The passageway turns here and the air is " +
      "getting warmer still.  The strong odour of wyrmmen " +
      "fills the air.\n");
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_exit("/d/Rhovanion/mute/dungeon1/guard26","west");
   add_exit("/d/Rhovanion/mute/dungeon1/guard10","south");
}
