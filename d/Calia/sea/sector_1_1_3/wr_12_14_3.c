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
    make_the_room("\n", 12, 14, 3);

    add_swim_exit(SECTOR_PATH(12,13,3)+"wr_12_13_3", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(12,15,3)+"wr_12_15_3", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(11,14,3)+"wr_11_14_3", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(13,14,3)+"wr_13_14_3", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(11,13,3)+"wr_11_13_3", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(11,15,3)+"wr_11_15_3", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(13,13,3)+"wr_13_13_3", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(12,14,2)+"wr_12_14_2", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(12,14,4)+"wr_12_14_4", "down", 0, 2);
}
