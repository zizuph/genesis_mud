
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("Ruined Road");
    set_long("This is a ruined road. To the northwest you see the " +
             "tangled mess of the ruined city gates. You see a breach " +
             "in the wall to the north and the road continues to the " +
             "west.\n");

    add_swim_exit(MENISCA + "road2","west",0,1);
    add_swim_exit(MENISCA + "wall_breach","north",0,1);
}
