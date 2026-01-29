
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("A Path");
    set_long("This is a basic water room.\n");

    add_swim_exit(MENISCA + "path1","east",0,1);
    add_swim_exit(MENISCA + "path3","northwest",0,1);
    add_swim_exit(MENISCA + "shop1","west",0,1);
}
