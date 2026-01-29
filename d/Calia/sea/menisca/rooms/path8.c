
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("A crossroads");
    set_long("This is a crossroads. There is a large building to the west. " +
             "Oddly enough, it looks to be in fairly good repair, reletively speaking. " +
             "The path continues north and south, while a ruined road leads " +
             "east.\n");

    /* Patrol area */

    add_swim_exit(MENISCA + "path7","north",0,1);
    add_swim_exit(MENISCA + "path9","south",0,1);
    add_swim_exit(MENISCA + "lib1","west",0,1);
    add_swim_exit(MENISCA + "road6","east",0,1);
}
