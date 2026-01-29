
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

    add_swim_exit(MENISCA + "path*","north",0,1);    
    add_swim_exit(MENISCA + "path*","northeast",0,1);
    add_swim_exit(MENISCA + "path*","east",0,1);    
    add_swim_exit(MENISCA + "path*","southeast",0,1);
    add_swim_exit(MENISCA + "path*","south",0,1);    
    add_swim_exit(MENISCA + "path*","southwest",0,1);
    add_swim_exit(MENISCA + "path*","west",0,1);    
    add_swim_exit(MENISCA + "path*","northwest",0,1);
}
