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
    make_the_room("\n", 6, 15, 0);

    add_swim_exit(SECTOR_PATH(6,14,0)+"6_14_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(5,15,0)+"5_15_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(7,15,0)+"7_15_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(5,14,0)+"5_14_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(7,14,0)+"7_14_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(6,14,0)+"6_14_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(5,15,0)+"5_15_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(7,15,0)+"7_15_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(5,14,0)+"5_14_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(7,14,0)+"7_14_0", "northwest", 0, 1);
}
