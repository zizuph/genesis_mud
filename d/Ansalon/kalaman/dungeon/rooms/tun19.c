#include "local.h"

inherit DUNGEON_IN;

create_dungeon_room()
{
   set_dungeon_type(ROOM_TUNNEL1);
   ::create_dungeon_room();

   set_long(get_long_desc() + "The only way that seems accessable from here " +
      "is to the southeast, anywhere else just seems too narrow.\n");

   add_exit("tun12", "southeast", 0, 5, 1);
}
