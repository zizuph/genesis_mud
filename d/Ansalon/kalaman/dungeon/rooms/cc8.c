#include "local.h"

inherit DUNGEON_IN;

create_dungeon_room()
{
   set_dungeon_type(ROOM_CLROW1);
   ::create_dungeon_room();

   add_exit("cc7", "south");

   add_cell_door("kmancell9",({ "west", "w" }), DUNGEON + "cell9", "west", CELL_KEY1);
   add_cell_door("kmancell0",({ "east", "e" }), DUNGEON + "cell0", "east", CELL_KEY1);
}
