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
    make_the_room("\n", 5, 6, 0);

    add_swim_exit(SECTOR_PATH(5,5,0)+"5_5_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(5,7,0)+"5_7_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(4,6,0)+"4_6_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(6,6,0)+"6_6_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(4,5,0)+"4_5_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(4,7,0)+"4_7_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(6,5,0)+"6_5_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(6,7,0)+"6_7_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(5,5,0)+"5_5_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(5,7,0)+"5_7_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(4,6,0)+"4_6_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(6,6,0)+"6_6_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(4,5,0)+"4_5_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(4,7,0)+"4_7_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(6,5,0)+"6_5_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(6,7,0)+"6_7_0", "southwest", 0, 1);
}
