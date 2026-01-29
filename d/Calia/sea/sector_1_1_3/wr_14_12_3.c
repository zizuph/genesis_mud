/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_1_3_room";

void
create_water_room()
{
    make_the_room("\n", 14, 12, 3);

    add_swim_exit(SECTOR_PATH(14,11,3)+"wr_14_11_3", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(14,13,3)+"wr_14_13_3", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(13,12,3)+"wr_13_12_3", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(15,12,3)+"wr_15_12_3", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(13,11,3)+"wr_13_11_3", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(13,13,3)+"wr_13_13_3", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(15,11,3)+"wr_15_11_3", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(14,12,2)+"wr_14_12_2", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(14,12,4)+"wr_14_12_4", "down", 0, 2);
}
