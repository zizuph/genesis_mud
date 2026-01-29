/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Gondor/sea/sector_0_0_0/sector_room";

void
create_water_room()
{
    make_the_room("\n", 7, 4, 0);

    add_swim_exit(SECTOR_PATH(7,3,0)+"7_3_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(7,5,0)+"7_5_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(6,4,0)+"6_4_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(8,4,0)+"8_4_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(6,3,0)+"6_3_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(6,5,0)+"6_5_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(8,3,0)+"8_3_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(8,5,0)+"8_5_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(7,3,0)+"7_3_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(7,5,0)+"7_5_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(6,4,0)+"6_4_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(8,4,0)+"8_4_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(6,3,0)+"6_3_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(6,5,0)+"6_5_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(8,3,0)+"8_3_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(8,5,0)+"8_5_0", "southwest", 0, 1);
}
