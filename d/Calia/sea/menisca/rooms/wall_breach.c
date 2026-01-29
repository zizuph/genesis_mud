
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("Wall Breach");
    set_long("This is a breach in the wall that allows ingress into the ruins.\n");

    add_swim_exit(MENISCA + "road1","south",0,1);
    add_swim_exit(MENISCA + "road2","southwest",0,1);
}
