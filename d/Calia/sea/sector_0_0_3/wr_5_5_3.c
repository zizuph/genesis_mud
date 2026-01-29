/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_0_3_room";

#include "seasnake.h"

void
create_water_room()
{
    make_the_room("\n", 5, 5, 3);

    add_swim_exit(SECTOR_PATH(5,4,3)+"wr_5_4_3", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(5,6,3)+"wr_5_6_3", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(6,5,3)+"wr_6_5_3", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(6,4,3)+"wr_6_4_3", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(6,6,3)+"wr_6_6_3", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(5,5,2)+"wr_5_5_2", "up", 0, 0);
    reset_room();
}
