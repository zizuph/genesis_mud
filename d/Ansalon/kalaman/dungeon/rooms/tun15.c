#include "local.h"

inherit DUNGEON_IN;

create_dungeon_room()
{
   set_dungeon_type(ROOM_TUNNEL1);
   ::create_dungeon_room();

   set_long(get_long_desc() + " The only way that seems accessable from here " +
      "is to the east and west, anywhere else just seems too narrow, however " +
      "it might be possible to crawl northwards as well.\n");

   add_exit("tun14", "northwest", 0, 5, 1);
   add_exit("tun17", "north", 0, 25, 1);
   add_exit("tun16", "east", 0, 5, 1);
}
