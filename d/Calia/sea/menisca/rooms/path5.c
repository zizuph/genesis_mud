
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("A path");
    set_long("This path meanders down a cleared alley through " +
             "the piles of rubble to either side.\n");

    add_swim_exit(MENISCA + "road5","west",0,1);
    add_swim_exit(MENISCA + "path6","east",0,1);
}
