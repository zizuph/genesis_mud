
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("A road");
    set_long("This is a road.\n");

    add_swim_exit(MENISCA + "path21","north",0,1);    
    add_swim_exit(MENISCA + "road10","east",0,1);    
    add_swim_exit(MENISCA + "path16","south",0,1);    
    add_swim_exit(MENISCA + "shop3","west",0,1);    

}
