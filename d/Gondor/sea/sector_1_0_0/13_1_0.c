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
    make_the_room("\n", 13, 1, 0);

    add_swim_exit(SECTOR_PATH(13,2,0)+"13_2_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(12,1,0)+"12_1_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(12,0,0)+"12_0_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(12,2,0)+"12_2_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(14,2,0)+"14_2_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(13,2,0)+"13_2_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(12,1,0)+"12_1_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(12,0,0)+"12_0_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(12,2,0)+"12_2_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(14,2,0)+"14_2_0", "southwest", 0, 1);
}
