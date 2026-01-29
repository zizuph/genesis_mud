
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("A muddy path.");
    set_long("This path leads into the greater part of the city ruins.\n");

    add_swim_exit(MENISCA + "path4","north",0,1);
    add_swim_exit(MENISCA + "path8","south",0,1);
}
