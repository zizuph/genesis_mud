
/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

inherit "/d/Gondor/sea/sector_0_0_0/sector_room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"


void
create_water_room()
{
    make_the_room("\n", 7, 3, 0);

    add_swim_exit(SECTOR_PATH(7,2,0)+"7_2_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(7,4,0)+"7_4_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(6,3,0)+"6_3_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(8,3,0)+"8_3_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(6,2,0)+"6_2_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(6,4,0)+"6_4_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(8,2,0)+"8_2_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(8,4,0)+"8_4_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(7,2,0)+"7_2_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(7,4,0)+"7_4_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(6,3,0)+"6_3_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(8,3,0)+"8_3_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(6,2,0)+"6_2_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(6,4,0)+"6_4_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(8,2,0)+"8_2_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(8,4,0)+"8_4_0", "southwest", 0, 1);

    reset_room(); 
}
