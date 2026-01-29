inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("This was Mute's!\n");
   set_long("The long, dark passageway bends here.  " +
      "A hot breeze is blowing from the northwest carrying " +
      "with it the over-powering scent of some reptilian " +
      "beast.  It is uncomfortably warm here.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/guard35","northwest");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/guard33","east");
}
