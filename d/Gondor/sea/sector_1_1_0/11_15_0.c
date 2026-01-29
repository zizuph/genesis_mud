/*
  Southwest area of Bay of Belfalas near Tolfalas island.

  Palmer - Aug 2006

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Gondor/sea/sector_1_1_0/sector_room";

 
void
create_water_room()
{
    make_the_room("\n", 11, 15, 0);

    add_swim_exit(SECTOR_PATH(11,14,0)+"11_14_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(10,15,0)+"10_15_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(12,15,0)+"12_15_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(10,14,0)+"10_14_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(12,14,0)+"12_14_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(11,14,0)+"11_14_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(10,15,0)+"10_15_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(12,15,0)+"12_15_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(10,14,0)+"10_14_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(12,14,0)+"12_14_0", "northwest", 0, 1);

    reset_room();
}

