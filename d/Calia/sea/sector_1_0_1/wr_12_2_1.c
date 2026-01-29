/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_0_1_room";

#include "seasnake.h"

void
create_water_room()
{
    make_the_room("\n", 12, 2, 1);

    add_swim_exit(SECTOR_PATH(12,1,1)+"wr_12_1_1", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(12,3,1)+"wr_12_3_1", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(11,2,1)+"wr_11_2_1", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(13,2,1)+"wr_13_2_1", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(11,1,1)+"wr_11_1_1", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(11,3,1)+"wr_11_3_1", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(13,1,1)+"wr_13_1_1", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(13,3,1)+"wr_13_3_1", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(12,2,0)+"wr_12_2_0", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(12,2,2)+"wr_12_2_2", "down", 0, 2);
    reset_room();
}
