#include "local.h"

inherit DUNGEON_IN;

#define THIS_ROOM "cc3"
#define exitN DROOM + gAdjacent[THIS_ROOM]["n"]
#define exitS DROOM + gAdjacent[THIS_ROOM]["s"]
#define exitW DROOM + gAdjacent[THIS_ROOM]["w"]

create_dungeon_room()
{
   ::create_dungeon_room();
   set_dungeon_type(ROOM_CLROW1);

   add_exit(exitW, "west");

   add_item(({"window", "windows"}), "There is a window in each of the two " +
     "cell doors here.\n");

   add_item(({"north window","window in north door"}), &add_cell_window(exitN));
   add_item(({"south window","window in south door"}), &add_cell_window(exitS));

   add_cell_door("kmancell1",({ "north", "s" }), exitN, "north", CELL_KEY1);
   add_cell_door("kmancell4",({ "south", "s" }), exitS, "south", CELL_KEY1);
}
