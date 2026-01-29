#include "local.h"

inherit DUNGEON_IN;

create_dungeon_room()
{
   set_dungeon_type(ROOM_GUARD1);
   ::create_dungeon_room();

   add_exit("dc1", "east");

   add_npc(DNPC + "dungeon_guard", 1);
}
