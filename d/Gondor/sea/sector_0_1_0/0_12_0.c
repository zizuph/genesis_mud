/*
  Southeast Bay of Belfalas near Tolfalas Island.

 Palmer - Aug 2006

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Gondor/sea/sector_0_1_0/sector_room";

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
    make_the_room("\n", 0, 12, 0);

    add_wade_exit(SECTOR_PATH(0,11,0)+"0_11_0", "north", 0, 1);
    add_wade_exit(SECTOR_PATH(1,12,0)+"1_12_0", "west", 0, 1);
    add_wade_exit(SECTOR_PATH(1,11,0)+"1_11_0", "northwest", 0, 1);
    add_wade_exit(SECTOR_PATH(1,13,0)+"1_13_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(0,11,0)+"0_11_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(1,12,0)+"1_12_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(1,11,0)+"1_11_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(1,13,0)+"1_13_0", "southwest", 0, 1);

    reset_room(); 
}

