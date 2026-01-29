
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

    add_swim_exit(MENISCA + "ptem5","west",0,1);
    add_swim_exit(MENISCA + "ptem6","northwest",0,1);
    add_swim_exit(MENISCA + "ptem1","north",0,1);
    add_swim_exit(MENISCA + "ptem3","east",0,1);
    add_swim_exit(MENISCA + "ptem2","northeast",0,1);
}
