/*
   Wayreth.

   forest03.c
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
   add_exit(WFOREST + "forest01", "north", 0, 2);
   add_exit(WFOREST + "forest08", "south", 0, 2);
   add_exit(WFOREST + "forest02", "west", 0, 2);
} 
