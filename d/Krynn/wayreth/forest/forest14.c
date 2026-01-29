/*
   Wayreth.

   forest14.c
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
   add_exit(WFOREST + "forest15", "east", 0, 2);
   add_exit(WFOREST + "forest21", "south", 0, 2);
}

