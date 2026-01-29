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
    make_the_room("\n", 2, -3, -1);

    add_swim_exit(SECTOR_PATH(1, -3, -1) + "1_-3_-1", "west", 0);
    add_row_exit(SECTOR_PATH(1, -3, -1) + "1_-3_-1", "west", 0);
    add_swim_exit(SECTOR_PATH(3, -3, -1) + "3_-3_-1", "east", 0);
    add_row_exit(SECTOR_PATH(3, -3, -1) + "3_-3_-1", "east", 0);
    add_swim_exit(SECTOR_PATH(2, -3, 0) + "2_-3_0", "up", 0);
    add_row_exit(SECTOR_PATH(2, -3, 0) + "2_-3_0", "up", 0);
    add_swim_exit(SECTOR_PATH(2, -2, -1) + "2_-2_-1", "south", 0);
    add_row_exit(SECTOR_PATH(2, -2, -1) + "2_-2_-1", "south", 0);
    add_swim_exit(SECTOR_PATH(1, -2, -1) + "1_-2_-1", "southwest", 0);
    add_row_exit(SECTOR_PATH(1, -2, -1) + "1_-2_-1", "southwest", 0);

}

