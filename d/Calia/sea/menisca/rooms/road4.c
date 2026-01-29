
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("Ruined Road");
    set_long("THAT DOES IT! You better turn around before you " +
             "break a leg, or better yet, your neck! East is the " +
             "path to safety.  The road northwest is best described " +
             "as barely a traversable path.\n");

    add_swim_exit(MENISCA + "road3","east",0,1);
    add_swim_exit(MENISCA + "path1","northwest",0,1);
}
