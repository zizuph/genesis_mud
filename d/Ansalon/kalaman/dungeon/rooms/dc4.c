#include "local.h"

inherit DUNGEON_IN;

create_dungeon_room()
{
   set_dungeon_type(ROOM_MAIN);
   ::create_dungeon_room();

   add_exit("dc3", "north");
//   add_exit("dg1", "west");
//   add_exit("dg2", "east");
}
