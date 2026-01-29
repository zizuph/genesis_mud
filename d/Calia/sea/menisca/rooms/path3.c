
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("A muddy path");
    set_long("A muddy path that leads in a bunch of directions. " +
             "There is a ruined shop to the east.\n");

    add_swim_exit(MENISCA + "path4","southwest",0,1);
    add_swim_exit(MENISCA + "path2","southeast",0,1);
    add_swim_exit(MENISCA + "road5","north",0,1);
    add_swim_exit(MENISCA + "shop2","east",0,1);
}
