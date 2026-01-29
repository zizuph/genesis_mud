#include "local.h"

inherit DUNGEON_IN;

create_dungeon_room()
{
   set_dungeon_type(ROOM_TUNNEL1);
   ::create_dungeon_room();

   set_long(get_long_desc() + " There seems to more space both to " +
      "the south and the north of here.\n");

   add_exit("tun8", "north", 0, 5, 1);
   add_exit("tun10", "south", 0, 5, 1);
}
