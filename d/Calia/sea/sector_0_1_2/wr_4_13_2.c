/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_1_2_room";

#include "seasnake.h"

void
create_water_room()
{
    make_the_room("\n", 4, 13, 2);

    add_swim_exit(SECTOR_PATH(4,12,2)+"wr_4_12_2", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(4,14,2)+"wr_4_14_2", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(3,13,2)+"wr_3_13_2", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(5,13,2)+"wr_5_13_2", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(3,12,2)+"wr_3_12_2", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(3,14,2)+"wr_3_14_2", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(5,12,2)+"wr_5_12_2", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(5,14,2)+"wr_5_14_2", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(4,13,1)+"wr_4_13_1", "up", 0, 0);
    reset_room();
}
