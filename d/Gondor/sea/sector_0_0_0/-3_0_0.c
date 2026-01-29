/*

  A room in the Bay of Belfalas near Tolfalas island.

  Palmer - Aug 24, 2006

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Gondor/sea/sector_1_0_0/sector_room";

void
create_water_room()
{
    make_the_room("\n", -3, 0, 0);

    add_swim_exit(SECTOR_PATH(-2, 1, 0) + "-2_1_0", "southeast", 0);
    add_row_exit(SECTOR_PATH(-2, 1, 0) + "-2_1_0", "southeast", 0);
    add_swim_exit(SECTOR_PATH(-2, 0, 0) + "-2_0_0", "east", 0);
    add_row_exit(SECTOR_PATH(-2, 0, 0) + "-2_0_0", "east", 0);
    add_swim_exit(SECTOR_PATH(-3, -1, 0) + "-3_-1_0", "north", 0);
    add_row_exit(SECTOR_PATH(-3, -1, 0) + "-3_-1_0", "north", 0);
    add_swim_exit(SECTOR_PATH(-3, 1, 0) + "-3_1_0", "south", 0);
    add_row_exit(SECTOR_PATH(-3, 1, 0) + "-3_1_0", "south", 0);

}

