
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("A Road");
    set_long("This is a road.\n");

    add_swim_exit(MENISCA + "lib1","east",0,1);    
    add_swim_exit(MENISCA + "road14","west",0,1);    

}
