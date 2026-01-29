inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room()
{
   set_short("shaft");
   set_long("You are in the middle of a round, vertical shaft of large, dark stones.  Above you is the tunnel you climbed down from.  Just below you lies an inky black darkness from which your ears detect the distinct sound of chitonous appendages upon the stone passageways below.  A shiver tingles down your spine as you ponder what horrors you might find below...  and perhaps what treasure, as well!\n");
   add_item(({"stone","stones"}), "The stones comprising this shaft are not uniform nor do they appear as if worked by a master stoneworker.  Instead, the stones appear as if hastily, yet not too shabbily, set here into these walls.");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/spilair1","up");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/spilair3","down");
}
