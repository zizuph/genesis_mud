
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("Seating area");
    set_long("From the amount of rotten wood and rusted railings " +
             "laying about, you discern that a great number of pews " +
             "used to be here. They were presumably set up to watch " +
             "the ceremonies that were held in the greathall to the " +
             "north. There is a narrow hallway that leads to the " +
             "northwest and a passage that exits to the west.\n");

    add_swim_exit(MENISCA + "dtem6","east",0,1);
    add_swim_exit(MENISCA + "dtem4","south",0,1);
    add_swim_exit(MENISCA + "dtem1","southeast",0,1);
}
