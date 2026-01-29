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
    make_the_room("\n", 8, 3, 0);

    add_swim_exit(SECTOR_PATH(8,2,0)+"8_2_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(8,4,0)+"8_4_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(7,3,0)+"7_3_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(9,3,0)+"9_3_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(7,2,0)+"7_2_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(7,4,0)+"7_4_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(9,2,0)+"9_2_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(9,4,0)+"9_4_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(8,2,0)+"8_2_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(8,4,0)+"8_4_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(7,3,0)+"7_3_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(9,3,0)+"9_3_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(7,2,0)+"7_2_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(7,4,0)+"7_4_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(9,2,0)+"9_2_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(9,4,0)+"9_4_0", "southwest", 0, 1);
}
