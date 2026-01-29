
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("Ruined Road");
    set_long("This is part of a ruined road. To the west and south " +
             "you see crumbling guard towers. The road continues east and " +
             "to the southwest. Northeast takes you back to the breach.\n");


    add_swim_exit(MENISCA + "guard1","west",0,1);
    add_swim_exit(MENISCA + "guard2","south",0,1);
    add_swim_exit(MENISCA + "road3","southwest",0,1);
    add_swim_exit(MENISCA + "road1","east",0,1);
    add_swim_exit(MENISCA + "wall_breach","northeast",0,1);
}
