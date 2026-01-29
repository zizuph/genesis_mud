/*
 * Ticket for ship between Flotsam and Faerun
 * -- Finwe, January 2006
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include "defs.h"
#include "/d/Faerun/defs.h"
#include <stdproperties.h>

void
create_object()
{
    set_name("ticket");
    add_name(FLOTSAM_TICKET_NAME);
    add_adj("diamond-shaped");
    set_long("This is a weathered piece of hard paper cut in the shape of a diamond. Stamped on the front you see the words, 'Good for travel between Balifor and Faerun on the Sea Lion'.\n");

    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_VALUE, 24);
}
