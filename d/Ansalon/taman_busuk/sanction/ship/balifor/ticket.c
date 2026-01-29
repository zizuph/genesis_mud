inherit "/std/object";
#include "local.h"
#include <stdproperties.h>

void
create_object()
{
    set_name("ticket");
    add_name(TICKET_NAME);
    set_adj("blue");
    add_adj("dragon-marked");
    set_long("The ticket is blue and marked with a five-headed dragon. " +
        "It appears to give passage between Port Balifor and Sanction.\n");
    add_prop(OBJ_I_VALUE, 17);
}
