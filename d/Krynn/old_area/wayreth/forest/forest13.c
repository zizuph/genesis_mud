/*
   Wayreth.

   forest13.c
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
   add_exit(WFOREST + "forest07", "north", 0, 2);
   add_exit(WFOREST + "forest08", "northeast", 0, 2);
   add_exit(WFOREST + "forest20", "south", 0, 2);
}

