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
    make_the_room("\n", 8, 14, 0);

    add_swim_exit(SECTOR_PATH(8,13,0)+"8_13_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(8,15,0)+"8_15_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(7,14,0)+"7_14_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(9,14,0)+"9_14_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(7,13,0)+"7_13_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(7,15,0)+"7_15_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(9,13,0)+"9_13_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(9,15,0)+"9_15_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(8,13,0)+"8_13_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(8,15,0)+"8_15_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(7,14,0)+"7_14_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(9,14,0)+"9_14_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(7,13,0)+"7_13_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(7,15,0)+"7_15_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(9,13,0)+"9_13_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(9,15,0)+"9_15_0", "southwest", 0, 1);
}
