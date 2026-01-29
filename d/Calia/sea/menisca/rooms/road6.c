
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("Ruined road.");
    set_long("This is a ruined road. Toppled statues and colonades " +
             "line it.  There is a crossing in the path to the west. " +
             "A large stone building stands to the east.\n");

    add_swim_exit(MENISCA + "path8","west",0,1);
    add_swim_exit(MENISCA + "atem1","east",0,1);
}
