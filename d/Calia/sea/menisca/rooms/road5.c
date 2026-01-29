
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("Ruined road.");
    set_long("Broken and tilted cobblestones make footing rather " +
             "treacherous here. You could seriously hurt yourself " +
             "if you don't watch your step.\n");

    add_swim_exit(MENISCA + "path3","south",0,1);
    add_swim_exit(MENISCA + "path5","east",0,1);
}
