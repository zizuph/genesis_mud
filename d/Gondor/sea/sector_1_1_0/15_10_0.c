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
    make_the_room("\n", 15, 10, 0);

    add_swim_exit(SECTOR_PATH(15,9,0)+"15_9_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(15,11,0)+"15_11_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(14,10,0)+"14_10_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(14,9,0)+"14_9_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(14,11,0)+"14_11_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(15,9,0)+"15_9_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(15,11,0)+"15_11_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(14,10,0)+"14_10_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(14,9,0)+"14_9_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(14,11,0)+"14_11_0", "southeast", 0, 1);
}
