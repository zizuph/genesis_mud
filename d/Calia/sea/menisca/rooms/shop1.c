
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("Ruined shop");
    set_long("This is a ruined shop.  There isn't anything of " +
             "interest here, however if you want to search the piles " +
             "of rubble, feel free to do so.\n");

    add_swim_exit(MENISCA + "path2","east",0,1);
}
