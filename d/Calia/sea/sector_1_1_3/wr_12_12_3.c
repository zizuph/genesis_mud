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
    make_the_room("\n", 12, 12, 3);

    add_swim_exit(SECTOR_PATH(12,11,3)+"wr_12_11_3", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(12,13,3)+"wr_12_13_3", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(11,12,3)+"wr_11_12_3", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(13,12,3)+"wr_13_12_3", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(11,11,3)+"wr_11_11_3", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(11,13,3)+"wr_11_13_3", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(13,11,3)+"wr_13_11_3", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(13,13,3)+"wr_13_13_3", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(12,12,2)+"wr_12_12_2", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(12,12,4)+"wr_12_12_4", "down", 0, 2);
}
