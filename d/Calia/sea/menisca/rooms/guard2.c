
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("Ruined Guard Tower");
    set_long("A caved in guard tower. Water-krougs provide a " +
             "warm welcome.  There is the door to the north and " +
             "a hole in the west wall to crawl through.\n");

    add_swim_exit(MENISCA + "road2","north",0,1);
    add_swim_exit(MENISCA + "road3","west",0,1);
}
