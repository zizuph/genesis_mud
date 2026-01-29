/*
  Southeast Bay of Belfalas near Tolfalas Island.

 Palmer - Aug 2006

*/

inherit "/d/Gondor/sea/sector_0_1_0/sector_room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"


void
create_water_room()
{
    make_the_room("\n", 2, 10, 0);

    add_swim_exit(SECTOR_PATH(2,9,0)+"2_9_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(2,11,0)+"2_11_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(1,10,0)+"1_10_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(3,10,0)+"3_10_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(1,9,0)+"1_9_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(1,11,0)+"1_11_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(3,9,0)+"3_9_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(3,11,0)+"3_11_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(2,9,0)+"2_9_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(2,11,0)+"2_11_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(1,10,0)+"1_10_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(3,10,0)+"3_10_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(1,9,0)+"1_9_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(1,11,0)+"1_11_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(3,9,0)+"3_9_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(3,11,0)+"3_11_0", "southwest", 0, 1);

    reset_room(); 
}
