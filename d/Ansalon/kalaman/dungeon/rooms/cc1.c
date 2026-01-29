#include "local.h"

inherit DUNGEON_IN;

#define THIS_ROOM "cc1"
#define exitN DROOM + gAdjacent[THIS_ROOM]["n"]
#define exitS DROOM + gAdjacent[THIS_ROOM]["s"]
#define exitE DROOM + gAdjacent[THIS_ROOM]["e"]
#define exitW DROOM + gAdjacent[THIS_ROOM]["w"]

create_dungeon_room()
{
   ::create_dungeon_room();
   set_dungeon_type(ROOM_CLROW1);

   add_exit(exitW, "west");
   add_exit(exitE, "east");

   add_item(({"north window", "window in north door", "north cell", "north bars", 
     "north cell bars", "northern cell"}), &add_cell_window(exitN));
   add_item(({"south window","window in south door", "south cell", "south bars", 
     "south cell bars", "southern cell"}), &add_cell_window(exitS));

   add_cell_door("kmancell1",({ "north", "s" }), exitN, "north", CELL_KEY1);
   add_cell_door("kmancell4",({ "south", "s" }), exitS, "south", CELL_KEY1);
}
