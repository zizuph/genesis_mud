#include "local.h"

inherit DUNGEON_IN;

create_dungeon_room()
{
   set_dungeon_type(ROOM_TUNNEL2);
   ::create_dungeon_room();

   set_long(get_long_desc() + " There seems to be room to carefully move " +
      "upwards and southwards here.\n");

   add_exit("tun3", "up", 0, 5, 1);
   add_exit("tun5", "south", 0, 5, 1);
}
