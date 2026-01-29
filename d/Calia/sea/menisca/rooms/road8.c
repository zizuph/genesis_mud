
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("A Road.");
    set_long("This is a road.\n");

    add_swim_exit(MENISCA + "house2","east",0,1);    
    add_swim_exit(MENISCA + "path13","south",0,1);    
    add_swim_exit(MENISCA + "road7","west",0,1);    

}
