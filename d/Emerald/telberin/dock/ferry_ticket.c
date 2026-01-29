inherit "/std/object";

#include "../defs.h"

#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    set_name("ticket");
    add_name("Telberin to North Shore Line");
    add_adj("crumpled");
    add_adj("brown");
    set_long("It looks like a ticket to some ship.\n");
    add_prop(OBJ_I_VALUE, 10);
}

query_recover()   { return MASTER; }
