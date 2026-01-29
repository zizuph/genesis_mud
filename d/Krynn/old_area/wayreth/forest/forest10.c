/*
   Wayreth.

   forest10.c
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

   add_exit(WFOREST + "forest04", "north", 0, 2);
   add_exit(WFOREST + "forest11", "east", 0, 2);
   add_exit(WFOREST + "@@connecting_room", "southeast", 0, 2);
   add_exit(WFOREST + "forest17", "south", 0, 2);
   add_exit(WFOREST + "forest09", "west", 0, 2);
}

