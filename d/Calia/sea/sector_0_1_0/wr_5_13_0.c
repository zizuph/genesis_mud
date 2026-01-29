/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_1_0_room";

#include "fisherman.h"

void
create_water_room()
{
    make_the_room("\n", 5, 13, 0);

    add_swim_exit(SECTOR_PATH(5,12,0)+"wr_5_12_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(5,14,0)+"wr_5_14_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(4,13,0)+"wr_4_13_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(6,13,0)+"wr_6_13_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(4,12,0)+"wr_4_12_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(4,14,0)+"wr_4_14_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(6,12,0)+"wr_6_12_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(6,14,0)+"wr_6_14_0", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(5,13,1)+"wr_5_13_1", "down", 0, 2);
    add_row_exit(SECTOR_PATH(5,12,0)+"wr_5_12_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(5,14,0)+"wr_5_14_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(4,13,0)+"wr_4_13_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(6,13,0)+"wr_6_13_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(4,12,0)+"wr_4_12_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(4,14,0)+"wr_4_14_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(6,12,0)+"wr_6_12_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(6,14,0)+"wr_6_14_0", "southwest", 0, 1);

    reset_room(); 
}
