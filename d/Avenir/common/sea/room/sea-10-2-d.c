/*
 * Mariner's berth 
 */

#include "../defs.h"

inherit AVENIR_SEA +"avenir_sea-d";

void
create_sea_room ()
{
    ::create_sea_room();
    add_row_exits(AVENIR_BERTH, "north", 0, 1);

    reset_sea_room();

    add_item(({"sybarus","port","harbour", "harbor","docks", 
        "landing", "berth"}),
        "North is the berth where Mariners can tie up their boats.\n");

}
