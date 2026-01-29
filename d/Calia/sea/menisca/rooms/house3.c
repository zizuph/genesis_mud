
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("A House");
    set_long("This is a house.\n");

    add_swim_exit(MENISCA + "path12","north",0,1);    

}
