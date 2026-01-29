/*
   Wayreth.

   forest19.c
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

   add_exit(WFOREST + "forest12", "north", 0, 2);
   add_exit(WFOREST + "forest20", "east", 0, 2);
   add_exit(WFOREST + "@@connecting_room", "west", 0, 2);
}

