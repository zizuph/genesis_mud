inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("man\n");
   set_long("This part of the passageway is in a serious state of " +
      "disrepair.  The large, stone blocks that are the walls and " +
      "ceiling are old and rough;  the air is nearly too stale to " +
      "breathe;  and there is a slight slant of the passage to the " +
      "south making you question the safety of being here.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun35","northwest");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/cell1","northeast");
}
