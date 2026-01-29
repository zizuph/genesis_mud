
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("A Shop");
    set_long("This is a shop.\n");

    add_swim_exit(MENISCA + "path21","west",0,1);    

}
