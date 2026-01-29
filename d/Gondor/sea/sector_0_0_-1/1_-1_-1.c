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
    make_the_room("\n", 1, -1, -1);

    add_swim_exit(SECTOR_PATH(0, -1, -1) + "0_-1_-1", "west", 0);
    add_row_exit(SECTOR_PATH(0, -1, -1) + "0_-1_-1", "west", 0);
    add_swim_exit(SECTOR_PATH(2, -1, -1) + "2_-1_-1", "east", 0);
    add_row_exit(SECTOR_PATH(2, -1, -1) + "2_-1_-1", "east", 0);
    add_swim_exit(SECTOR_PATH(1, -2, -1) + "1_-2_-1", "north", 0);
    add_row_exit(SECTOR_PATH(1, -2, -1) + "1_-2_-1", "north", 0);
    add_swim_exit(SECTOR_PATH(1, 0, -1) + "1_0_-1", "south", 0);
    add_row_exit(SECTOR_PATH(1, 0, -1) + "1_0_-1", "south", 0);

}

