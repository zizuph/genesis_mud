/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_1_4_room";

#include "shark.h"

void
create_water_room()
{
    make_the_room("\n", 12, 14, 4);

    add_swim_exit(SECTOR_PATH(12,13,4)+"wr_12_13_4", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(12,15,4)+"wr_12_15_4", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(11,14,4)+"wr_11_14_4", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(13,14,4)+"wr_13_14_4", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(11,13,4)+"wr_11_13_4", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(11,15,4)+"wr_11_15_4", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(13,13,4)+"wr_13_13_4", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(12,14,3)+"wr_12_14_3", "up", 0, 0);
    reset_room();
}
