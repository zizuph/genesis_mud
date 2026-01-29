#include "local.h"

inherit DUNGEON_IN;

create_dungeon_room()
{
   set_dungeon_type(ROOM_CLROW2);
   ::create_dungeon_room();

   add_exit("cc5", "west");
}
