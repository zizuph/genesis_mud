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
    make_the_room("\n", 6, 0, 0);

    add_swim_exit(SECTOR_PATH(6,1,0)+"6_1_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(5,0,0)+"5_0_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(7,0,0)+"7_0_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(5,1,0)+"5_1_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(7,1,0)+"7_1_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(6,1,0)+"6_1_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(5,0,0)+"5_0_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(7,0,0)+"7_0_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(5,1,0)+"5_1_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(7,1,0)+"7_1_0", "southwest", 0, 1);
}
