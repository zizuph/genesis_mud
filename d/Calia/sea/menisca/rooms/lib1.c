
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("Library portico.");
    set_long("This is the porch entrance to a ruined library.\n");

    add_swim_exit(MENISCA + "path14","north",0,1);    
    add_swim_exit(MENISCA + "path8","east",0,1);    
    add_swim_exit(MENISCA + "path10","south",0,1);    
    add_swim_exit(MENISCA + "road15","west",0,1);    

}
