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
    make_the_room("\n", 5, 12, 0);

    add_swim_exit(SECTOR_PATH(5,11,0)+"5_11_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(5,13,0)+"5_13_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(4,12,0)+"4_12_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(6,12,0)+"6_12_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(4,11,0)+"4_11_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(4,13,0)+"4_13_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(6,11,0)+"6_11_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(6,13,0)+"6_13_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(5,11,0)+"5_11_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(5,13,0)+"5_13_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(4,12,0)+"4_12_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(6,12,0)+"6_12_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(4,11,0)+"4_11_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(4,13,0)+"4_13_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(6,11,0)+"6_11_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(6,13,0)+"6_13_0", "southwest", 0, 1);
}
