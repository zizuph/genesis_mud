
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("A path");
    set_long("This is a path. There are the ruins of a house " +
             "to the south.\n");

    add_swim_exit(MENISCA + "path5","west",0,1);
    add_swim_exit(MENISCA + "house1","south",0,1);
}
