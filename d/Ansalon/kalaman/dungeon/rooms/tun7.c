#include "local.h"

inherit DUNGEON_IN;

create_dungeon_room()
{
   set_dungeon_type(ROOM_TUNNEL2);
   ::create_dungeon_room();

   set_long(get_long_desc() + " One could move both towards the east and southeast " +
      "here, but it looks narrow.\n");

   add_exit("tun6", "east", 0, 5, 1);
   add_exit("tun8", "southeast", 0, 5, 1);
}
