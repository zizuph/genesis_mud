
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("A road.");
    set_long("This is a road.\n");

    add_swim_exit(MENISCA + "path27","north",0,1);    
    add_swim_exit(MENISCA + "path28","east",0,1);    
    add_swim_exit(MENISCA + "path26","south",0,1);    
    add_swim_exit(MENISCA + "path30","southwest",0,1);
    add_swim_exit(MENISCA + "path29","west",0,1);    

}
