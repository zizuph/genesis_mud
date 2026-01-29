
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("Temple foyer.");
    set_long("You walk up the broad semicircle stairs to enter the " +
             "main foyer.  Scattered pieces of statuettes and mosiac " +
             "litter the area.  A grand arched hallwy leads east as " +
             "open doorways invite you north and south. Lesser halls " +
             "branch to the northeast and southeast. The road lies " +
             "back to the west.\n");

    add_swim_exit(MENISCA + "road14","east",0,1);
    add_swim_exit(MENISCA + "dtem6","north",0,1);
    add_swim_exit(MENISCA + "dtem5","northwest",0,1);
    add_swim_exit(MENISCA + "dtem4","west",0,1);
    add_swim_exit(MENISCA + "dtem3","southwest",0,1);
    add_swim_exit(MENISCA + "dtem2","south",0,1);
}
