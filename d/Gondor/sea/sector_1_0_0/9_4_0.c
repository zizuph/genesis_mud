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
    make_the_room("\n", 9, 4, 0);

    add_swim_exit(SECTOR_PATH(9,3,0)+"9_3_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(9,5,0)+"9_5_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(8,4,0)+"8_4_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(10,4,0)+"10_4_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(8,3,0)+"8_3_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(8,5,0)+"8_5_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(10,3,0)+"10_3_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(10,5,0)+"10_5_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(9,3,0)+"9_3_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(9,5,0)+"9_5_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(8,4,0)+"8_4_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(10,4,0)+"10_4_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(8,3,0)+"8_3_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(8,5,0)+"8_5_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(10,3,0)+"10_3_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(10,5,0)+"10_5_0", "southwest", 0, 1);
}
