#pragma strict_types

inherit "/std/object.c";

#include "/d/Faerun/defs.h"
#include <macros.h>
#include <stdproperties.h>

#define well            this_object()

int water_drawn = 0;

void
create_object()
{
    set_name("well");
    set_adj("old");
    set_adj("very");
	set_long("This is an old well.\n");
//	add_cmd_item(({ "well","" }));

    add_item(({"well"}),
        "There is a very old well in the center of the sideyard, it appears " +
        "as if it once held water, but no longer. There is a bucket seated " +
        "on the edge of the well, with an old rope attached and tied to a " +
        "crank.\n");
}

int 
water_drawn();
{
    
}
