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
    make_the_room("\n", -1, -2, 0);

    add_swim_exit(SECTOR_PATH(-1, -3, 0) + "-1_-3_0", "north", 0);
    add_row_exit(SECTOR_PATH(-1, -3, 0) + "-1_-3_0", "north", 0);
    add_swim_exit(SECTOR_PATH(-2, -2, 0) + "-2_-2_0", "west", 0);
    add_row_exit(SECTOR_PATH(-2, -2, 0) + "-2_-2_0", "west", 0);
    add_swim_exit(SECTOR_PATH(0, -1, 0) + "0_-1_0", "southeast", 0);
    add_row_exit(SECTOR_PATH(0, -1, 0) + "0_-1_0", "southeast", 0);
    add_swim_exit(SECTOR_PATH(-2, -3, 0) + "-2_-3_0", "northwest", 0);
    add_row_exit(SECTOR_PATH(-2, -3, 0) + "-2_-3_0", "northwest", 0);
    add_swim_exit(SECTOR_PATH(0, -2, 0) + "0_-2_0", "east", 0);
    add_row_exit(SECTOR_PATH(0, -2, 0) + "0_-2_0", "east", 0);
    add_swim_exit(SECTOR_PATH(-1, -1, 0) + "-1_-1_0", "south", 0);
    add_row_exit(SECTOR_PATH(-1, -1, 0) + "-1_-1_0", "south", 0);

}

