inherit "/std/object";
#include "local.h"
#include <stdproperties.h>

void
create_object()
{
    set_name("ticket");
    add_name(TICKET_NAME);
    set_adj("crumpled");
    add_adj("old");
    set_long("It looks like a ticket to the ferry across the Vingaard River at " +
	     "Vingaard Keep.\n");
    add_prop(OBJ_I_VALUE, 25);
}
