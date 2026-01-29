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
    make_the_room("\n", 9, 1, 0);

    add_swim_exit(SECTOR_PATH(9,0,0)+"9_0_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(9,2,0)+"9_2_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(8,1,0)+"8_1_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(10,1,0)+"10_1_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(8,0,0)+"8_0_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(8,2,0)+"8_2_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(10,0,0)+"10_0_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(10,2,0)+"10_2_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(9,0,0)+"9_0_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(9,2,0)+"9_2_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(8,1,0)+"8_1_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(10,1,0)+"10_1_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(8,0,0)+"8_0_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(8,2,0)+"8_2_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(10,0,0)+"10_0_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(10,2,0)+"10_2_0", "southwest", 0, 1);
}
