/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_1_3_room";

void
create_water_room()
{
    make_the_room("\n", 6, 13, 3);

    add_swim_exit(SECTOR_PATH(6,12,3)+"wr_6_12_3", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(6,14,3)+"wr_6_14_3", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(5,13,3)+"wr_5_13_3", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(7,13,3)+"wr_7_13_3", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(5,12,3)+"wr_5_12_3", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(5,14,3)+"wr_5_14_3", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(7,12,3)+"wr_7_12_3", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(7,14,3)+"wr_7_14_3", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(6,13,2)+"wr_6_13_2", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(6,13,4)+"wr_6_13_4", "down", 0, 2);
}
