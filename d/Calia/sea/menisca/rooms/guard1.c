
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("A ruined guard tower");
    set_long("This guard tower is crumbling and falling in on itself." +
             "Water-krougs will be here.  There is the door to the east " +
             "and a hole in the south wall to leave by.\n");

    add_swim_exit(MENISCA + "road2","east",0,1);
    add_swim_exit(MENISCA + "road3","south",0,1);
}
