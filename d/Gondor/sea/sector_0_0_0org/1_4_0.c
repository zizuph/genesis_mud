/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Gondor/sea/sector_0_0_0/sector_room";

object crab;

void
reset_room()
{
    if (!objectp(crab)) {  
        crab = clone_object(SEA_CREATURES+"crab"); 
        crab->move_living("into the sea", this_object()); 
    } 
}


void
create_water_room()
{
    make_the_room("\n", 1, 4, 0);

    add_wade_exit(SECTOR_PATH(1,5,0)+"1_5_0", "south", 0, 1);
    add_wade_exit(SECTOR_PATH(0,4,0)+"0_4_0", "east", 0, 1);
    add_wade_exit(SECTOR_PATH(2,4,0)+"2_4_0", "west", 0, 1);
    add_wade_exit(SECTOR_PATH(0,5,0)+"0_5_0", "southeast", 0, 1);
    add_wade_exit(SECTOR_PATH(2,3,0)+"2_3_0", "northwest", 0, 1);
    add_wade_exit(SECTOR_PATH(2,5,0)+"2_5_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(1,5,0)+"1_5_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(0,4,0)+"0_4_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(2,4,0)+"2_4_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(0,5,0)+"0_5_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(2,3,0)+"2_3_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(2,5,0)+"2_5_0", "southwest", 0, 1);

    reset_room(); 
}

