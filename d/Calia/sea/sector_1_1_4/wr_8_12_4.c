/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_1_4_room";

void
create_water_room()
{
    make_the_room("\n", 8, 12, 4);

    add_swim_exit(SECTOR_PATH(8,11,4)+"wr_8_11_4", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(8,13,4)+"wr_8_13_4", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(7,12,4)+"wr_7_12_4", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(9,12,4)+"wr_9_12_4", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(7,11,4)+"wr_7_11_4", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(7,13,4)+"wr_7_13_4", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(9,11,4)+"wr_9_11_4", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(9,13,4)+"wr_9_13_4", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(8,12,3)+"wr_8_12_3", "up", 0, 0);
}
