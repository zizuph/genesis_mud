#include "local.h"

inherit DUNGEON_IN;

create_dungeon_room()
{
   set_dungeon_type(ROOM_TUNNEL1);
   ::create_dungeon_room();

   set_long(get_long_desc() + " A little bit towards the west some more " +
      "room seems accessable and also to the northeast.\n");

   add_exit("tun5", "northeast", 0, 5, 1);
   add_exit("tun7", "west", 0, 5, 1);
}
