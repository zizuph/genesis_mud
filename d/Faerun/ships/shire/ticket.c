/*
 * Ticket for ship between Shire and Faerun
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
    add_name(SHIRE_TICKET_NAME);
    add_adj("rectangular");
    set_long("This ticket is rectangular shaped and made from a piece of hard paper. Stamped on the front you see the words, 'Good for travel between Shire and Faerun'.\n");

    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_VALUE, 24);
}
