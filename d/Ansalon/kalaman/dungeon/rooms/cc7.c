#include "local.h"

inherit DUNGEON_IN;

create_dungeon_room()
{
   set_dungeon_type(ROOM_CLROW1);
   ::create_dungeon_room();

   add_exit("cc8", "north");
   add_exit("dcE", "south");

   add_cell_door("kmancell7",({ "west", "w" }), DUNGEON + "cell7", "west", CELL_KEY1);
   add_cell_door("kmancell8",({ "east", "e" }), DUNGEON + "cell8", "east", CELL_KEY1);
}
