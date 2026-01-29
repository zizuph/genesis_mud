
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

    add_swim_exit(MENISCA + "dtem1","east",0,1);
    add_swim_exit(MENISCA + "dtem2","southeast",0,1);
    add_swim_exit(MENISCA + "dtem3","south",0,1);
    add_swim_exit(MENISCA + "dtem5","north",0,1);
    add_swim_exit(MENISCA + "dtem6","northeast",0,1);
}
