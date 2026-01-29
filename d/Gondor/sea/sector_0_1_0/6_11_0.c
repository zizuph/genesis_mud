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
    make_the_room("\n", 6, 11, 0);

    add_swim_exit(SECTOR_PATH(6,10,0)+"6_10_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(6,12,0)+"6_12_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(5,11,0)+"5_11_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(7,11,0)+"7_11_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(5,10,0)+"5_10_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(5,12,0)+"5_12_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(7,10,0)+"7_10_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(7,12,0)+"7_12_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(6,10,0)+"6_10_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(6,12,0)+"6_12_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(5,11,0)+"5_11_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(7,11,0)+"7_11_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(5,10,0)+"5_10_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(5,12,0)+"5_12_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(7,10,0)+"7_10_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(7,12,0)+"7_12_0", "southwest", 0, 1);
 
    reset_room(); 
}

