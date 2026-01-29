
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("Ceremonial room.");
    set_long("This is a large greatroom where once religious " +
             "ceremonies were held. A large empty niche in " +
             "the east wall presumably held the statue that lies " +
             "in pieces directly before it. A cracked altar sits " +
             "in the middle of this room. Multiple exits lead " +
             "to other parts of the temple.\n");

    add_swim_exit(MENISCA + "gtem1","south",0,1);
    add_swim_exit(MENISCA + "gtem2","southwest",0,1);
    add_swim_exit(MENISCA + "gtem3","west",0,1);
    add_swim_exit(MENISCA + "gtem5","east",0,1);
    add_swim_exit(MENISCA + "gtem6","southeast",0,1);
}
