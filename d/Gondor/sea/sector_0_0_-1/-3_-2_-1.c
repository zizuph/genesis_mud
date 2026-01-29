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
    make_the_room("\n", -3, -2, -1);

    add_swim_exit(SECTOR_PATH(-2, -2, -1) + "-2_-2_-1", "east", 0);
    add_row_exit(SECTOR_PATH(-2, -2, -1) + "-2_-2_-1", "east", 0);
    add_swim_exit(SECTOR_PATH(-3, -3, -1) + "-3_-3_-1", "north", 0);
    add_row_exit(SECTOR_PATH(-3, -3, -1) + "-3_-3_-1", "north", 0);
    add_swim_exit(SECTOR_PATH(-3, -2, 0) + "-3_-2_0", "up", 0);
    add_row_exit(SECTOR_PATH(-3, -2, 0) + "-3_-2_0", "up", 0);
    add_swim_exit(SECTOR_PATH(-3, -1, -1) + "-3_-1_-1", "south", 0);
    add_row_exit(SECTOR_PATH(-3, -1, -1) + "-3_-1_-1", "south", 0);

}

