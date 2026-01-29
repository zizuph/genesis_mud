#pragma strict_types

inherit "/std/object.c";

#include <macros.h>
#include <stdproperties.h>

#define BS(message)     break_string(message, 75)
#define TP              this_player()
#define well            this_object()

void
create_object()
{
    set_name("An old well");
	
	add_cmd_item(({ "well","" }));

set_long(({"well"}),
        "There is a very old well in the center of the sideyard, it appears " +
        "as if it once held water, but no longer. There is a bucket seated " +
        "on the edge of the well, with an old rope attached and tied to a " +
        "crank.\n");
}
