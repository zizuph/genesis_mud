/* stairwy1.c: Bottom of staircase. Serpine, 4-24-95. */
#pragma save_binary

inherit "/d/Cirath/std/room";
#include "defs.h"

void
create_room()
{
   set_short("bottom of staircase");
   set_long("Here in the northwest corner of the building sits a massive "+
            "stone staircase that spirals up towards the lair of the "+
            "warriors. The walls are literally covered with carvings, "+
            "though none go far down the hallway to the east.\n");

   add_item(({"carving", "carvings", "wall", "walls"}), "They are images "+
            "of battle, glory, and death in the arena: The meat and drink "+
            "the beings who reside in this structure.\n");

   add_item(({"staircase", "stone staircase"}), "The sounds of battle "+
            "echo from above.\n");

   INSIDE

   add_exit(PSION_ROOM + "mainhall.c", "east", 0, 1);
   add_exit(PSION_ROOM + "stairwy2.c", "up", 0, 1);
}