#include "local.h"

inherit DUNGEON_IN;

create_dungeon_room()
{
   set_dungeon_type(ROOM_MAIN);
   ::create_dungeon_room();

   add_exit("sq1", "west");
   add_exit("dc8", "east");
   add_exit("dcA", "south");
}
