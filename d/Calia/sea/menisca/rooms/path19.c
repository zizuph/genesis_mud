
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("A Path, Barely");
    set_long("This is a path.\n");

    add_swim_exit(MENISCA + "path16","east",0,1);    
    add_swim_exit(MENISCA + "path17","southeast",0,1);
    add_swim_exit(MENISCA + "path18","south",0,1);    

}
