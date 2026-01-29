inherit "/std/object";
#include "local.h"
#include <stdproperties.h>

void
create_object()
{
    set_name("ticket");
    add_name(TICKET_NAME);
    add_adj("white");
    add_adj("skull");
    set_long("It looks like just another ship ticket, almost. " +
	     "There is a small skull in one corner.\n");
    add_prop(OBJ_I_VALUE, 18);
}
