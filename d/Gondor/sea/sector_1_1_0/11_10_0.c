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
    make_the_room("\n", 11, 10, 0);

    add_swim_exit(SECTOR_PATH(11,9,0)+"11_9_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(11,11,0)+"11_11_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(10,10,0)+"10_10_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(12,10,0)+"12_10_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(10,9,0)+"10_9_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(10,11,0)+"10_11_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(12,9,0)+"12_9_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(12,11,0)+"12_11_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(11,9,0)+"11_9_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(11,11,0)+"11_11_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(10,10,0)+"10_10_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(12,10,0)+"12_10_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(10,9,0)+"10_9_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(10,11,0)+"10_11_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(12,9,0)+"12_9_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(12,11,0)+"12_11_0", "southwest", 0, 1);
}
