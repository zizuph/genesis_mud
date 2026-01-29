#include "local.h"

inherit DUNGEON_IN;

create_dungeon_room()
{
   set_dungeon_type(ROOM_MAIN);
   ::create_dungeon_room();

   add_exit("dc2", "north");
   add_exit("dc4", "south");
   add_exit("cg2", "west");
   add_exit("cc4", "east");
}
