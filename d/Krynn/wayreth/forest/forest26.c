/*
   Wayreth.

   forest26.c
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

   add_exit(WFOREST + "forest31", "southeast", 0, 2);
   add_exit(WFOREST + "forest30", "south", 0, 2);
   add_exit(WFOREST + "forest25", "west", 0, 2);
   add_exit(WFOREST + "@@connecting_room", "northwest", 0, 2);
}

