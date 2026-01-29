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
    make_the_room("\n", 8, 9, 0);

    add_swim_exit(SECTOR_PATH(8,8,0)+"8_8_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(8,10,0)+"8_10_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(7,9,0)+"7_9_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(9,9,0)+"9_9_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(7,8,0)+"7_8_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(7,10,0)+"7_10_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(9,8,0)+"9_8_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(9,10,0)+"9_10_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(8,8,0)+"8_8_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(8,10,0)+"8_10_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(7,9,0)+"7_9_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(9,9,0)+"9_9_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(7,8,0)+"7_8_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(7,10,0)+"7_10_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(9,8,0)+"9_8_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(9,10,0)+"9_10_0", "southwest", 0, 1);
}
