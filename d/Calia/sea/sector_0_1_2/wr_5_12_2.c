/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_1_2_room";

void
create_water_room()
{
    make_the_room("\n", 5, 12, 2);

    add_swim_exit(SECTOR_PATH(5,11,2)+"wr_5_11_2", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(5,13,2)+"wr_5_13_2", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(4,12,2)+"wr_4_12_2", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(6,12,2)+"wr_6_12_2", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(4,11,2)+"wr_4_11_2", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(4,13,2)+"wr_4_13_2", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(6,11,2)+"wr_6_11_2", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(6,13,2)+"wr_6_13_2", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(5,12,1)+"wr_5_12_1", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(5,12,3)+"wr_5_12_3", "down", 0, 2);
}
