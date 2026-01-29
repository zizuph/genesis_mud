/*
  Southeast Bay of Belfalas near Tolfalas Island.

 Palmer - Aug 2006

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Gondor/sea/sector_0_1_0/sector_room";

void
create_water_room()
{
    make_the_room("\n", 5, 14, 0);

    add_swim_exit(SECTOR_PATH(5,13,0)+"5_13_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(5,15,0)+"5_15_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(4,14,0)+"4_14_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(6,14,0)+"6_14_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(4,13,0)+"4_13_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(4,15,0)+"4_15_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(6,13,0)+"6_13_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(6,15,0)+"6_15_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(5,13,0)+"5_13_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(5,15,0)+"5_15_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(4,14,0)+"4_14_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(6,14,0)+"6_14_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(4,13,0)+"4_13_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(4,15,0)+"4_15_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(6,13,0)+"6_13_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(6,15,0)+"6_15_0", "southwest", 0, 1);
}
