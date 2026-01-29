/*
 * Ticket for ship between Faerie and VK
 * -- Finwe, January 2006
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include "defs.h"
#include <stdproperties.h>

void
create_object()
{
    set_name("ticket");
    add_name("_faerie_vk_ticket_");
    add_adj("paper");
    set_long("This ticket is valid for the boat that sails between " +
	"Faerie and Vingaard Keep.\n");

    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_VALUE, 24);
}
