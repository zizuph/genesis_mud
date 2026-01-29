/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_0_1_room";

void
create_water_room()
{
    make_the_room("\n", 12, 5, 1);

    add_swim_exit(SECTOR_PATH(12,4,1)+"wr_12_4_1", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(12,6,1)+"wr_12_6_1", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(11,5,1)+"wr_11_5_1", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(13,5,1)+"wr_13_5_1", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(11,4,1)+"wr_11_4_1", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(11,6,1)+"wr_11_6_1", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(13,4,1)+"wr_13_4_1", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(13,6,1)+"wr_13_6_1", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(12,5,0)+"wr_12_5_0", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(12,5,2)+"wr_12_5_2", "down", 0, 2);
}
