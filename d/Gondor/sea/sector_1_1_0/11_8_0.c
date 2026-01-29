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
    make_the_room("\n", 11, 8, 0);

    add_swim_exit(SECTOR_PATH(11,7,0)+"11_7_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(11,9,0)+"11_9_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(10,8,0)+"10_8_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(12,8,0)+"12_8_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(10,7,0)+"10_7_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(10,9,0)+"10_9_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(12,7,0)+"12_7_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(12,9,0)+"12_9_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(11,7,0)+"11_7_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(11,9,0)+"11_9_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(10,8,0)+"10_8_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(12,8,0)+"12_8_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(10,7,0)+"10_7_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(10,9,0)+"10_9_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(12,7,0)+"12_7_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(12,9,0)+"12_9_0", "southwest", 0, 1);
}
