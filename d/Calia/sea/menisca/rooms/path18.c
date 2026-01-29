
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

    add_swim_exit(MENISCA + "path19","north",0,1);    
    add_swim_exit(MENISCA + "path16","northeast",0,1);
    add_swim_exit(MENISCA + "path17","east",0,1);    
    add_swim_exit(MENISCA + "path20","northwest",0,1);
}
