
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("A shop.");
    set_long("This is a shop.\n");

    add_swim_exit(MENISCA + "road11","east",0,1);    

}
