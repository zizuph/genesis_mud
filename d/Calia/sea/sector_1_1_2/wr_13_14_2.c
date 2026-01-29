/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_1_2_room";

#include "dolphin.h"

void
create_water_room()
{
    make_the_room("\n", 13, 14, 2);

    add_swim_exit(SECTOR_PATH(13,13,2)+"wr_13_13_2", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(12,14,2)+"wr_12_14_2", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(12,13,2)+"wr_12_13_2", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(12,15,2)+"wr_12_15_2", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(14,13,2)+"wr_14_13_2", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(13,14,1)+"wr_13_14_1", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(13,14,3)+"wr_13_14_3", "down", 0, 2);
    reset_room();
}
