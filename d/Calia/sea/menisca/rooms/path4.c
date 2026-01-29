
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("A path");
    set_long("This path continues to the south.  You can " +
             "count your blessings and head back to the " +
             "northeast if you're wise.\n");

    add_swim_exit(MENISCA + "path7","south",0,1);
    add_swim_exit(MENISCA + "path3","northeast",0,1);
}
