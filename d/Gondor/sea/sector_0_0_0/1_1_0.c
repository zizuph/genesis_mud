/*

  A room in the Bay of Belfalas near Tolfalas island.

  Palmer - Aug 24, 2006

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Gondor/sea/sector_1_0_0/sector_room";

void
create_water_room()
{
    make_the_room("\n", 1, 1, 0);

    add_swim_exit(SECTOR_PATH(1, 0, 0) + "1_0_0", "north", 0);
    add_row_exit(SECTOR_PATH(1, 0, 0) + "1_0_0", "north", 0);
    add_swim_exit(SECTOR_PATH(0, 1, 0) + "0_1_0", "west", 0);
    add_row_exit(SECTOR_PATH(0, 1, 0) + "0_1_0", "west", 0);
    add_swim_exit(SECTOR_PATH(2, 2, 0) + "2_2_0", "southeast", 0);
    add_row_exit(SECTOR_PATH(2, 2, 0) + "2_2_0", "southeast", 0);
    add_swim_exit(SECTOR_PATH(0, 0, 0) + "0_0_0", "northwest", 0);
    add_row_exit(SECTOR_PATH(0, 0, 0) + "0_0_0", "northwest", 0);
    add_swim_exit(SECTOR_PATH(2, 1, 0) + "2_1_0", "east", 0);
    add_row_exit(SECTOR_PATH(2, 1, 0) + "2_1_0", "east", 0);
    add_swim_exit(SECTOR_PATH(1, 2, 0) + "1_2_0", "south", 0);
    add_row_exit(SECTOR_PATH(1, 2, 0) + "1_2_0", "south", 0);

}

