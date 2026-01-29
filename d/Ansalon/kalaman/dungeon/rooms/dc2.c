#include "local.h"

inherit DUNGEON_IN;

create_dungeon_room()
{
   set_dungeon_type(ROOM_MAIN);
   ::create_dungeon_room();

   add_exit("dc3", "south");
   add_exit("dc1", "north");
   add_exit("dc5", "west");
}
