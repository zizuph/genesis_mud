#include "local.h"

inherit DUNGEON_IN;

create_dungeon_room()
{
   set_dungeon_type(ROOM_TUNNEL1);
   ::create_dungeon_room();

   set_long(get_long_desc() + " There seems to be room to move " +
      "towards upwards and northwest here.\n");

   add_exit("tun10", "northwest", 0, 5, 1);
   add_exit("tun12", "up", 0, 5, 1);
}
