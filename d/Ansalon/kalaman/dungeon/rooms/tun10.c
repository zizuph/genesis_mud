#include "local.h"

inherit DUNGEON_IN;

create_dungeon_room()
{
   set_dungeon_type(ROOM_TUNNEL2);
   ::create_dungeon_room();

   set_long(get_long_desc() + " There seems to be room to move " +
      "towards the north and southeast.\n");

   add_exit("tun11", "southeast", 0, 5, 1);
   add_exit("tun9", "north", 0, 5, 1);
}
