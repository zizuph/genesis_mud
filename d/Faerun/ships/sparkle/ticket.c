/*
 * Ticket for ship between Sparkle and Faerun
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
    add_name(SPARKLE_TICKET_NAME);
    add_adj("paper");
    set_long("This ticket is ratty looking and made from a piece of hard paper. It is good for the boat that sails between Sparkle and Faerun.\n");

    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_VALUE, 24);
}
