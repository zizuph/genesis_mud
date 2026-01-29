#include "/d/Krynn/wayreth/local.h"

inherit FORESTROOM;

void
create_forest_room()
{
    add_exit(HAVEN + "road/forest6", "east", 0, 3, 1);
    add_exit(WFOREST + "forest03", "south", 0 ,"@@fatigue",1);
    add_exit(WFOREST + "forest02", "southwest", 0, 3, 1);
} 
