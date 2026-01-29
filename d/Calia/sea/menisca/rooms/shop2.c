
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("A ruined shoppe");
    set_long("This appears to be a ruined bistro of some sorts. " +
             "A rotten counter with a pile of broken stools sits " +
             "along the north wall.\n");

    add_swim_exit(MENISCA + "path3","west",0,1);
}
