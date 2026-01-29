/*
   Wayreth.

   forest02.c
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
   set_normal_room("forest06");
   set_special_room("clearing");

   add_exit(WFOREST + "forest01", "northeast", 0, 2);
   add_exit(WFOREST + "forest03", "east", 0, 2);
   add_exit(WFOREST + "forest07", "south", 0, 2);
   add_exit(WFOREST + "@@connecting_room", "southwest", 0, 2);
} 
