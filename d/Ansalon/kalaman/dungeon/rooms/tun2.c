#include "local.h"

inherit DUNGEON_IN;

create_dungeon_room()
{
   set_dungeon_type(ROOM_TUNNEL1);
   ::create_dungeon_room();

   set_long(get_long_desc() + " There seems to be room to move " +
      "towards the south and the northwest here.\n");

   add_exit("tun3", "northwest", 0, 5, 1);
   add_exit("tun1", "south", 0, 5, 1);
}
