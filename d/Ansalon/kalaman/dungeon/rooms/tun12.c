#include "local.h"

inherit DUNGEON_IN;

create_dungeon_room()
{
   set_dungeon_type(ROOM_TUNNEL1);
   ::create_dungeon_room();

   set_long(get_long_desc() + " There seems to be room to move " +
      "towards the northwest and possible downwards here.\n");

   add_exit("tun13", "northwest", 0, 5, 1);
   add_exit("tun11", "down", 0, 5, 1);
}
