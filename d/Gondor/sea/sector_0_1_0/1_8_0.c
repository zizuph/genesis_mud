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
    make_the_room("\n", 1, 8, 0);

    add_wade_exit(SECTOR_PATH(1,7,0)+"1_7_0", "north", 0, 1);
    add_wade_exit(SECTOR_PATH(1,9,0)+"1_9_0", "south", 0, 1);
    add_wade_exit(SECTOR_PATH(0,8,0)+"0_8_0", "east", 0, 1);
    add_wade_exit(SECTOR_PATH(2,8,0)+"2_8_0", "west", 0, 1);
    add_wade_exit(SECTOR_PATH(0,7,0)+"0_7_0", "northeast", 0, 1);
    add_wade_exit(SECTOR_PATH(0,9,0)+"0_9_0", "southeast", 0, 1);
    add_wade_exit(SECTOR_PATH(2,7,0)+"2_7_0", "northwest", 0, 1);
    add_wade_exit(SECTOR_PATH(2,9,0)+"2_9_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(1,7,0)+"1_7_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(1,9,0)+"1_9_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(0,8,0)+"0_8_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(2,8,0)+"2_8_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(0,7,0)+"0_7_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(0,9,0)+"0_9_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(2,7,0)+"2_7_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(2,9,0)+"2_9_0", "southwest", 0, 1);
}
