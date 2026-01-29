/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Gondor/sea/sector_0_0_0/sector_room";

void
create_water_room()
{
    make_the_room("\n", 2, 3, 0);

    add_swim_exit(SECTOR_PATH(2,2,0)+"2_2_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(2,4,0)+"2_4_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(3,3,0)+"3_3_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(1,4,0)+"1_4_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(3,2,0)+"3_2_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(3,4,0)+"3_4_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(2,2,0)+"2_2_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(2,4,0)+"2_4_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(3,3,0)+"3_3_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(1,4,0)+"1_4_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(3,2,0)+"3_2_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(3,4,0)+"3_4_0", "southwest", 0, 1);
}
