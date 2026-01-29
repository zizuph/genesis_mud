
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("Ruined Road");
    set_long("This ruined road blows chunks.  You almost twisted " +
             "your ankle. It continues to the west, or you can " +
             "head for the hospital in Thallasia for medical attention " +
             "to the northeast.  Forboding holes in the buildings to " +
             "the north and east of you invite you to explore them " +
             "and likely get your head chopped off.\n");

    add_swim_exit(MENISCA + "guard1","north",0,1);
    add_swim_exit(MENISCA + "guard2","east",0,1);
    add_swim_exit(MENISCA + "road2","northeast",0,1);
    add_swim_exit(MENISCA + "road4","west",0,1);
}
