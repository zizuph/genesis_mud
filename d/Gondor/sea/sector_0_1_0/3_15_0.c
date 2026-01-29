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
    make_the_room("\n", 3, 15, 0);

    add_swim_exit(SECTOR_PATH(3,14,0)+"3_14_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(4,15,0)+"4_15_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(2,14,0)+"2_14_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(4,14,0)+"4_14_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(3,14,0)+"3_14_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(4,15,0)+"4_15_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(2,14,0)+"2_14_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(4,14,0)+"4_14_0", "northwest", 0, 1);
}
