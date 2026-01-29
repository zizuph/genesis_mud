/*
   Wayreth.

   forest18.c
   ----------

   Coded ........: 95/05/24
   By ...........: Jeremiah

   Latest update : 95/05/24
   By ...........: Jeremiah

*/


#include "/d/Krynn/wayreth/local.h"
inherit FORESTROOM;

void
create_forest_room()
{
   add_exit(WFOREST + "forest11", "north", 0, 2);
   add_exit(WFOREST + "forest12", "northeast", 0, 2);
   add_exit(WFOREST + "forest19", "east", 0, 2);
   add_exit(WFOREST + "forest26", "southeast", 0, 2);
   add_exit(WFOREST + "forest25", "south", 0, 2);
   add_exit(WFOREST + "forest24", "southwest", 0, 2);
   add_exit(WFOREST + "forest17", "west", 0, 2);
   add_exit(WFOREST + "forest10", "northwest", 0, 2);
}

