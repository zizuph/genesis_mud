/*
   Wayreth.

   forest12.c
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
   set_normal_room("forest18");
   set_special_room("clearing");

   add_exit(WFOREST + "forest06", "north", 0, 2);
   add_exit(WFOREST + "forest07", "northeast", 0, 2);
   add_exit(WFOREST + "forest19", "south", 0, 2);
   add_exit(WFOREST + "@@connecting_room", "southwest", 0, 2);
   add_exit(WFOREST + "forest11", "west", 0, 2);
}

