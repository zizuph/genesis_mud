
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("Basic water room");
    set_long("This is a basic water room.\n");

    add_swim_exit(MENISCA + "","direction",0,1);
}
