#include "local.h"

inherit DUNGEON_IN;

#define REMOTE_ROOM DROOM + "cc3"

create_dungeon_room()
{
   ::create_dungeon_room();
   set_dungeon_type(ROOM_CELL1);

   add_cell_door("kmancell1",({ "south", "s" }), REMOTE_ROOM, "south", CELL_KEY1);
   add_item(({ "corridor", "steel bars", "bars" }), &add_cell_window(REMOTE_ROOM));

   add_npc(DNPC + "dungeon_prisoner", random(3));
}
