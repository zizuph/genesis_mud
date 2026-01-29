/*
  Southwest area of Bay of Belfalas near Tolfalas island.

  Palmer - Aug 2006

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Gondor/sea/sector_1_1_0/sector_room";

void
create_water_room()
{
    make_the_room("\n", 13, 9, 0);

    add_swim_exit(SECTOR_PATH(13,8,0)+"13_8_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(13,10,0)+"13_10_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(12,9,0)+"12_9_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(14,9,0)+"14_9_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(12,8,0)+"12_8_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(12,10,0)+"12_10_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(14,8,0)+"14_8_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(14,10,0)+"14_10_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(13,8,0)+"13_8_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(13,10,0)+"13_10_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(12,9,0)+"12_9_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(14,9,0)+"14_9_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(12,8,0)+"12_8_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(12,10,0)+"12_10_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(14,8,0)+"14_8_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(14,10,0)+"14_10_0", "southwest", 0, 1);
}
