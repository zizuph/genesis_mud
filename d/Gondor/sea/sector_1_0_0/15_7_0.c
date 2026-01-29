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
    make_the_room("\n", 15, 7, 0);

    add_swim_exit(SECTOR_PATH(15,6,0)+"15_6_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(15,8,0)+"15_8_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(14,7,0)+"14_7_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(14,6,0)+"14_6_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(14,8,0)+"14_8_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(15,6,0)+"15_6_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(15,8,0)+"15_8_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(14,7,0)+"14_7_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(14,6,0)+"14_6_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(14,8,0)+"14_8_0", "southeast", 0, 1);
}
