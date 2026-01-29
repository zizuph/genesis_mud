
/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

  Connected to beach, Maniac, 30/7/96

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_1_0_room";

void
create_water_room()
{
    make_the_room("\n", 0, 9, 0);

    add_wade_exit(WATER+"beach/village1", "east", 0, 1); 
    add_wade_exit(SECTOR_PATH(0,8,0)+"wr_0_8_0", "north", 0, 1);
    add_wade_exit(SECTOR_PATH(0,10,0)+"wr_0_10_0", "south", 0, 1);
    add_wade_exit(SECTOR_PATH(1,9,0)+"wr_1_9_0", "west", 0, 1);
    add_wade_exit(SECTOR_PATH(1,8,0)+"wr_1_8_0", "northwest", 0, 1);
    add_wade_exit(SECTOR_PATH(1,10,0)+"wr_1_10_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(0,8,0)+"wr_0_8_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(0,10,0)+"wr_0_10_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(1,9,0)+"wr_1_9_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(1,8,0)+"wr_1_8_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(1,10,0)+"wr_1_10_0", "southwest", 0, 1);
}
