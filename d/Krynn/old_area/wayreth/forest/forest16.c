/*
   Wayreth.

   forest16.c
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
   set_normal_room("forest17");
   set_special_room("clearing");

   add_exit(WFOREST + "forest09", "north", 0, 2);
   add_exit(WFOREST + "@@connecting_room", "east", 0, 2);
   add_exit(WFOREST + "forest15", "west", 0, 2);
}

