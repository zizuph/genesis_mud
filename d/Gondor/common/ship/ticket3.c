#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
    set_name("ticket");
    add_name("The line from Gont Port to Gondor");
    add_adj("paper");
    set_long(break_string("This ticket is valid for the boatline between " +
	"Pelargir in Gondor and Gont Port in Earthsea.", 78) + "\n");
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_VALUE, 24);
}
