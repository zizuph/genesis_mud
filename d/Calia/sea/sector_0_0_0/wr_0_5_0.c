
/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

  Connected to beach, Maniac, 30/7/96

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_0_0_room";

void
create_water_room()
{
    make_the_room("\n", 0, 5, 0);

    add_wade_exit(WATER+"beach/beach2", "east", 0, 1); 
    add_wade_exit(SECTOR_PATH(0,4,0)+"wr_0_4_0", "north", 0, 1);
    add_wade_exit(SECTOR_PATH(0,6,0)+"wr_0_6_0", "south", 0, 1);
    add_wade_exit(SECTOR_PATH(1,5,0)+"wr_1_5_0", "west", 0, 1);
    add_wade_exit(SECTOR_PATH(1,4,0)+"wr_1_4_0", "northwest", 0, 1);
    add_wade_exit(SECTOR_PATH(1,6,0)+"wr_1_6_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(0,4,0)+"wr_0_4_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(0,6,0)+"wr_0_6_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(1,5,0)+"wr_1_5_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(1,4,0)+"wr_1_4_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(1,6,0)+"wr_1_6_0", "southwest", 0, 1);
}
